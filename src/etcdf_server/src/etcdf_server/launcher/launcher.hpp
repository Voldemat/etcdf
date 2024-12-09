#pragma once

#include <cstdint>
#include <optional>
#include "ipaddress/ip-any-address.hpp"
namespace etcdf::server::launcher {
void start_both_servers(const ipaddress::ip_address &httpHost, const uint16_t &httpPort,
                      const std::optional<unsigned int> &httpThreadCount,
                      const ipaddress::ip_address &grpcHost, const uint16_t &grpcPort);
};
