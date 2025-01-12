#pragma once

#include <memory>

#include "etcdf_server/shared/config.hpp"
#include "etcdf_server/shared/server_handle.hpp"

namespace etcdf::server::v3_grpc {
std::shared_ptr<shared::ServerHandle> create_grpcserver(
    const shared::Config &config);
};
