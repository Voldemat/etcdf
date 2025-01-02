#include "./config.hpp"

#include <netdb.h>
#include <netinet/in.h>
#include <sys/_endian.h>
#include <sys/socket.h>
#include <yaml-cpp/node/node.h>
#include <yaml-cpp/node/parse.h>
#include <yaml-cpp/yaml.h>

#include <cassert>
#include <cerrno>
#include <cstdio>
#include <cstring>
#include <format>
#include <fstream>
#include <iostream>
#include <ipaddress/errors.hpp>
#include <ipaddress/ip-any-address.hpp>
#include <ipaddress/ipv4-address.hpp>
#include <ipaddress/ipv6-address.hpp>
#include <optional>
#include <ranges>
#include <stdexcept>
#include <string>
#include <url.hpp>
#include <utility>
#include <vector>

#include "etcdf_server/shared/config.hpp"
#include "shared-utils/addrinfo_iterator.hpp"
#include "shared-utils/string_split.hpp"
#include "shared-utils/transform_utils.hpp"

namespace etcdf::cli::config {

etcdf::server::shared::EtcdfProtocol schemeToProtocol(
    const std::string &scheme) {
    server::shared::EtcdfProtocol protocol;
    if (scheme == "http") {
        return server::shared::EtcdfProtocol::HTTP;
    } else if (scheme == "grpc") {
        return server::shared::EtcdfProtocol::GRPC;
    } else {
        throw std::runtime_error(
            "Only supported scheme values are \"http\" and \"grpc\"");
    };
};

std::optional<unsigned int> parsePort(const std::string &sPort) {
    if (sPort == "") return std::nullopt;
    int port = std::stoi(sPort);
    if (port <= 0) {
        throw std::runtime_error("Port must be unsigned integer");
    };
    return port;
};

ipaddress::ip_address ipaddressFromSockaddrIn(const sockaddr_in &addr) {
    switch (addr.sin_family) {
        case AF_INET: {
            return ipaddress::ipv4_address::from_uint(
                ntohl(addr.sin_addr.s_addr));
        }
        case AF_INET6: {
            return ipaddress::ipv6_address::from_uint(
                ntohl(addr.sin_addr.s_addr));
        }
        default: {
            throw std::runtime_error(
                std::format("Unsupported address family: {}", addr.sin_family));
        }
    };
};

sockaddr_in sockaddrInFromAddrInfo(const addrinfo &addrinfo) {
    return *(struct sockaddr_in *)addrinfo.ai_addr;
};

std::vector<ipaddress::ip_address> hostToIps(const std::string &host) {
    try {
        return { ipaddress::ip_address::parse(host) };
    } catch (const ipaddress::error &) {
    };
    struct addrinfo hints;
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags |= AI_PASSIVE;

    AddrInfoAdapter *result;
    int error =
        getaddrinfo(host.c_str(), nullptr, &hints, (addrinfo **)&result);
    if (error != 0) {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(error));
        throw std::runtime_error(
            "Host is not ipaddress and is not resolvable through dns");
    };
    return *result | std::views::transform(sockaddrInFromAddrInfo) |
           std::views::transform(ipaddressFromSockaddrIn) |
           std::ranges::to<std::vector>();
};

etcdf::server::shared::Config config_from_file(std::ifstream &file) {
    etcdf::server::shared::Config config;
    auto node = YAML::Load(file);
    if (!node.IsMap()) {
        throw std::runtime_error("Config must be a yaml map");
    };
    config.dataDirPath = node["data-dir"].as<std::string>();
    const auto &advertisedClientUrls =
        node["advertise-client-urls"].as<std::string>();
    config.listeners.advertisedToClients =
        split(advertisedClientUrls, ",") |
        std::views::transform(transform_convert<Url>) |
        std::views::transform(
            [](const Url &url) -> server::shared::AdvertisedEndpoint {
                return { .host = url.host(),
                         .port = parsePort(url.port()),
                         .protocol = schemeToProtocol(url.scheme()) };
            }) |
        std::ranges::to<std::vector>();
    const auto &clientUrls = node["listen-client-urls"].as<std::string>();

    for (const auto &[protocol, endpoints] :
         split(clientUrls, ",") |
             std::views::transform(transform_convert<Url>) |
             std::views::transform(
                 [](const Url &url)
                     -> std::pair<server::shared::EtcdfProtocol,
                                  std::vector<server::shared::Endpoint>> {
                     const auto &port = parsePort(url.port());
                     const auto &endpoints =
                         hostToIps(url.host()) |
                         std::views::transform([&port](const auto &ip)
                                                   -> server::shared::Endpoint {
                             return { .ip_address = ip, .port = port.value() };
                         }) |
                         std::ranges::to<std::vector>();
                     return { schemeToProtocol(url.scheme()), endpoints };
                 })) {
        std::cout << std::format("{}: {}", (int)protocol, endpoints.size())
                  << std::endl;
        switch (protocol) {
            case server::shared::EtcdfProtocol::GRPC: {
                config.listeners.clients.grpc.append_range(endpoints);
                break;
            }
            case server::shared::EtcdfProtocol::HTTP: {
                config.listeners.clients.http.append_range(endpoints);
                break;
            }
        };
    };
    return config;
};
};  // namespace etcdf::cli::config
