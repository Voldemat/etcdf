#pragma once

#include "etcdf_server/shared/config.hpp"

namespace etcdf::server::v3_grpc {
void start_grpcserver(const shared::Config& config);
};
