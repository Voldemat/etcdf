#pragma once

#include "etcdf_server/shared/config.hpp"

namespace etcdf::server::v2_http {
void start_httpserver(const shared::Config &config);
};  // namespace etcdf::server::v2_http
