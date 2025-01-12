#pragma once

#include <memory>

#include "etcdf_server/shared/config.hpp"
#include "etcdf_server/shared/server_handle.hpp"

namespace etcdf::server::v2_http {
std::shared_ptr<shared::ServerHandle> create_httpserver(
    const shared::Config &config);
};  // namespace etcdf::server::v2_http
