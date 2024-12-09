#include "./server.hpp"

#include <cstdint>
#include <iostream>
#include <memory>
#include <optional>

#include "./first.hpp"
#include "drogon/HttpAppFramework.h"
#include "ipaddress/ip-any-address.hpp"

namespace etcdf::server::v2_http {
void start_httpserver(const ipaddress::ip_address &host, const uint16_t &port,
                      const std::optional<unsigned int> &threadCount) {
    const auto &controller = std::make_shared<TestController>();
    auto& app = drogon::app()
        .registerController(controller)
        .addListener(host.to_string(), port)
        .setThreadNum(threadCount.value_or(0));
    app.run();
    app.quit();
    std::cout << "start_httpserver ended" << std::endl;
};
};  // namespace etcdf::server
