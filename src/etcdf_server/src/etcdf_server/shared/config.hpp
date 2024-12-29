#pragma once

#include <filesystem>
#include <optional>
#include <string>
#include <tuple>
#include <vector>

#include "ipaddress/ip-any-address.hpp"

namespace etcdf::server::shared {
struct TLSContext {
    std::filesystem::path caPath;
    std::filesystem::path certPath;
    std::filesystem::path privateKeyPath;
};

enum class EtcdfProtocol { HTTP, GRPC };

struct Endpoint {
    ipaddress::ip_address ip_address;
    unsigned int port;
    std::optional<TLSContext> tlsContext;
};
using AdvertisedEndpoint = std::tuple<std::string, unsigned int, EtcdfProtocol>;

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
};
};  // namespace etcdf::server::shared
