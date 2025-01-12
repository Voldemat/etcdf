#include "./server.hpp"

#include <pthread.h>

#include <csignal>
#include <cstddef>
#include <memory>
#include <string>

#include "./first.hpp"
#include "drogon/HttpAppFramework.h"
#include "etcdf_server/shared/config.hpp"
#include "etcdf_server/shared/server_handle.hpp"
#include "etcdf_server/v2-http/http_server_handle.hpp"

namespace etcdf::server::v2_http {
std::shared_ptr<shared::ServerHandle> create_httpserver(
    const shared::Config &config) {
    const auto &controller = std::make_shared<TestController>();
    std::string host = "localhost";
    unsigned int port = 6000;
    return std::make_shared<HTTPServerHandle>(
        &drogon::app()
             .registerController(controller)
             .addListener(host, port)
             .disableSigtermHandling());
};
};  // namespace etcdf::server::v2_http
