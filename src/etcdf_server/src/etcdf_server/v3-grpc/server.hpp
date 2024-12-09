#pragma once

#include <cstdint>

#include "ipaddress/ip-any-address.hpp"
namespace etcdf::server::v3_grpc {
void start_grpcserver(const ipaddress::ip_address &host, const uint16_t &port);
};
