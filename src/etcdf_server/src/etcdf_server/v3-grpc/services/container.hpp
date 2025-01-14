#pragma once

#include "./auth/auth.hpp"
#include "./cluster/cluster.hpp"
#include "./kv/kv.hpp"
#include "./lease/lease.hpp"
#include "./maintenance/maintenance.hpp"
#include "./watch/watch.hpp"

namespace etcdf::server::v3_grpc {
struct ServicesContainer {
    GRPCKVService kvService;
    GRPCWatchService watchService;
    GRPCLeaseService leaseService;
    GRPCMaintenanceService maintenanceService;
    GRPCAuthService authService;
    GRPCClusterService clusterService;
};
};  // namespace etcdf::server::v3_grpc
