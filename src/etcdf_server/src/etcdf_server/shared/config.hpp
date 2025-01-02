#pragma once

#include <filesystem>
#include <ipaddress/ip-any-address.hpp>
#include <optional>
#include <string>
#include <vector>

namespace etcdf::server::shared {
struct TLSContext {
    std::optional<std::filesystem::path> caPath;
    std::filesystem::path certPath;
    std::filesystem::path privateKeyPath;
};

enum class EtcdfProtocol { HTTP, GRPC };

struct Endpoint {
    ipaddress::ip_address ip_address;
    unsigned int port;
    std::optional<TLSContext> tlsContext;
};

struct AdvertisedEndpoint {
    std::string host;
    std::optional<unsigned int> port;
    EtcdfProtocol protocol;
};

struct GrpcAndHttpListeners {
    std::vector<Endpoint> grpc;
    std::vector<Endpoint> http;
};

struct Config {
    struct Listeners {
        GrpcAndHttpListeners peers;
        GrpcAndHttpListeners clients;
        std::vector<AdvertisedEndpoint> advertisedToPeers;
        std::vector<AdvertisedEndpoint> advertisedToClients;
    } listeners;
    std::filesystem::path dataDirPath;
};
};  // namespace etcdf::server::shared
