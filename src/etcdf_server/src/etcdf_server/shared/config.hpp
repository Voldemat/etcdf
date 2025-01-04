#pragma once

#include <filesystem>
#include <ipaddress/ip-any-address.hpp>
#include <memory>
#include <optional>
#include <string>
#include <unordered_map>
#include <vector>

namespace etcdf::server::shared {
struct TLSContext {
    std::optional<std::filesystem::path> caPath;
    std::filesystem::path certPath;
    std::filesystem::path privateKeyPath;
};

struct Endpoint {
    ipaddress::ip_address ipAddress;
    unsigned int port;
    std::optional<std::shared_ptr<TLSContext>> tlsContext;
};

struct Config {
    struct Endpoints {
        std::vector<Endpoint> http;
        std::vector<Endpoint> grpc;
    } endpoints;
    std::unordered_map<std::string, std::shared_ptr<TLSContext>> tlsContexts;
    std::filesystem::path dataDirPath;
};
};  // namespace etcdf::server::shared
