#include "./server.hpp"

#include <cstdint>
#include <ipaddress/ipaddress.hpp>
#include <memory>
#include <optional>

#include "./first.hpp"
#include "drogon/HttpAppFramework.h"
#include "ipaddress/ip-any-address.hpp"

namespace etcdf::server {
void start_httpserver(const ipaddress::ip_address &host, const uint16_t &port,
                      const std::optional<unsigned int> &threadCount) {
    const auto &controller = std::make_shared<TestController>();
    const auto &check = drogon::app()
                            .registerController(controller)
                            .addListener(host.to_string(), port)
                            .setThreadNum(threadCount.value_or(0));
};
};  // namespace etcdf::server
