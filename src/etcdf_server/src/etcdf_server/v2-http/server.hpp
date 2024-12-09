#pragma once

#include <cstdint>
#include <ipaddress/ipaddress.hpp>
#include <optional>

#include "ipaddress/ip-any-address.hpp"

namespace etcdf::server::v2_http {
void start_httpserver(const ipaddress::ip_address &host, const uint16_t &port,
                      const std::optional<unsigned int> &threadCount);
};  // namespace etcdf::server
