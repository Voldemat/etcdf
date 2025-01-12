#include "./http_server_handle.hpp"

#include <drogon/HttpAppFramework.h>

namespace etcdf::server::v2_http {
HTTPServerHandle::HTTPServerHandle(drogon::HttpAppFramework *drogonApp)
    : drogonApp{ drogonApp } {};
void HTTPServerHandle::run() { drogonApp->run(); };
void HTTPServerHandle::stop() { drogonApp->quit(); };
};  // namespace etcdf::server::v2_http
