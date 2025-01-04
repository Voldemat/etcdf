#include "./config.hpp"

#include <netdb.h>
#include <netinet/in.h>
#include <sys/_endian.h>
#include <sys/socket.h>
#include <yaml-cpp/node/node.h>
#include <yaml-cpp/node/parse.h>
#include <yaml-cpp/node/type.h>
#include <yaml-cpp/yaml.h>

#include <cassert>
#include <cerrno>
#include <cstdio>
#include <cstring>
#include <filesystem>
#include <format>
#include <fstream>
#include <ipaddress/errors.hpp>
#include <ipaddress/ip-any-address.hpp>
#include <ipaddress/ipv4-address.hpp>
#include <ipaddress/ipv6-address.hpp>
#include <memory>
#include <optional>
#include <ranges>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include <url.hpp>
#include <utility>
#include <vector>

#include "etcdf_server/shared/config.hpp"
#include "shared-utils/addrinfo_iterator.hpp"

namespace etcdf::cli::config {

EndpointProtocol parseProtocol(const std::string &protocol) {
    if (protocol == "http") {
        return EndpointProtocol::HTTP;
    } else if (protocol == "grpc") {
        return EndpointProtocol::GRPC;
    } else {
        throw std::runtime_error(
            "Only supported protocol values are \"http\" and \"grpc\"");
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
    if (!std::filesystem::exists(config.dataDirPath)) {
        throw std::runtime_error("data-dir path does not exists");
    };
    if (!std::filesystem::is_directory(config.dataDirPath)) {
        throw std::runtime_error("data-dir is not a directory");
    };
    for (const auto &n : node["tlsContexts"]) {
    };
    const auto &tlsContexts =
        node["tlsContexts"] |
        std::views::transform(
            [](const YAML::detail::iterator_value &n)
                -> std::pair<std::string,
                             std::shared_ptr<server::shared::TLSContext>> {
                const auto &caPathNode = n.second["caPath"];
                server::shared::TLSContext tlsContext = {
                    .caPath = std::nullopt,
                    .certPath = n.second["certPath"].as<std::string>(),
                    .privateKeyPath =
                        n.second["privateKeyPath"].as<std::string>()
                };
                if (caPathNode.Type() != YAML::NodeType::Undefined) {
                    tlsContext.caPath = caPathNode.as<std::string>();
                };
                return { n.first.as<std::string>(),
                         std::make_shared<server::shared::TLSContext>(
                             tlsContext) };
            }) |
        std::ranges::to<std::unordered_map>();
    const auto &parsedEndpoints =
        node["endpoints"] |
        std::views::transform(
            [&tlsContexts](const YAML::Node &n)
                -> std::pair<EndpointProtocol, server::shared::Endpoint> {
                std::optional<std::shared_ptr<server::shared::TLSContext>>
                    tlsContext;
                const auto &tlsContextNode = n["tlsContext"];
                if (tlsContextNode.Type() != YAML::NodeType::Undefined) {
                    const auto &tlsContextName =
                        tlsContextNode.as<std::string>();
                    if (!tlsContexts.contains(tlsContextName)) {
                        throw std::runtime_error(std::format(
                            "tlsContext {} does not exist", tlsContextName));
                    };
                    tlsContext = tlsContexts.at(tlsContextName);
                };
                return { parseProtocol(n["protocol"].as<std::string>()),
                         { .ipAddress = ipaddress::ip_address::parse(
                               n["ipAddress"].as<std::string>()),
                           .port = n["port"].as<unsigned int>(),
                           .tlsContext = tlsContext } };
            }) |
        std::ranges::to<std::vector>();
    config.tlsContexts = tlsContexts;
    config.endpoints = {
        .http = parsedEndpoints | std::views::filter([](const auto &pair) {
                    return pair.first == EndpointProtocol::HTTP;
                }) |
                std::views::values | std::ranges::to<std::vector>(),
        .grpc = parsedEndpoints | std::views::filter([](const auto &pair) {
                    return pair.first == EndpointProtocol::GRPC;
                }) |
                std::views::values | std::ranges::to<std::vector>(),
    };
    return config;
};
};  // namespace etcdf::cli::config
