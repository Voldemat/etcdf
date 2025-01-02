#include "./server.hpp"

#include <iostream>
#include <memory>
#include <string>

#include "./first.hpp"
#include "drogon/HttpAppFramework.h"
#include "etcdf_server/shared/config.hpp"

namespace etcdf::server::v2_http {
void start_httpserver(const shared::Config &config) {
    const auto &controller = std::make_shared<TestController>();
    std::string host = "localhost";
    unsigned int port = 6000;
    auto &app = drogon::app()
                    .registerController(controller)
                    .addListener(host, port);
    app.run();
    app.quit();
};
};  // namespace etcdf::server::v2_http
