#include "./launcher.hpp"

#include <cstdint>
#include <optional>
#include <stdexcept>

#include "etcdf_server/v3-grpc/server.hpp"
#include "ipaddress/ip-any-address.hpp"

namespace etcdf::server::launcher {
void start_both_servers(const ipaddress::ip_address &httpHost,
                        const uint16_t &httpPort,
                        const std::optional<unsigned int> &httpThreadCount,
                        const ipaddress::ip_address &grpcHost,
                        const uint16_t &grpcPort) {
    if (httpHost == grpcHost && httpPort == grpcPort) {
        throw std::runtime_error(
            "Http and grpc should have different listener addresses.");
    };
    etcdf::server::v3_grpc::start_grpcserver(grpcHost, grpcPort);
};
};  // namespace etcdf::server::launcher
