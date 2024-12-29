#include "./launcher.hpp"

#include "etcdf_server/shared/config.hpp"
#include "etcdf_server/v3-grpc/server.hpp"

namespace etcdf::server::launcher {
void start_both_servers(const shared::Config &config) {
    etcdf::server::v3_grpc::start_grpcserver(config);
};
};  // namespace etcdf::server::launcher
