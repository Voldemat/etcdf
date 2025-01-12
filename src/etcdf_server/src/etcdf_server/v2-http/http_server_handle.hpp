#pragma once

#include <drogon/HttpAppFramework.h>

#include "etcdf_server/shared/server_handle.hpp"

namespace etcdf::server::v2_http {
class HTTPServerHandle : public shared::ServerHandle {
private:
    drogon::HttpAppFramework *drogonApp;

public:
    explicit HTTPServerHandle(drogon::HttpAppFramework *drogonApp);
    void run() override;
    void stop() override;
};
};  // namespace etcdf::server::v2_http
