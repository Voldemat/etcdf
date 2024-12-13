#include "./server.hpp"

#include <google/protobuf/empty.pb.h>
#include <grpcpp/grpcpp.h>
#include <grpcpp/security/credentials.h>
#include <grpcpp/security/server_credentials.h>
#include <grpcpp/support/status.h>
#include <grpcpp/support/sync_stream.h>

#include <cstdint>
#include <format>
#include <iostream>
#include <memory>
#include <string>

#include "etcdf_server/v3-grpc/services/auth/auth.hpp"
#include "etcdf_server/v3-grpc/services/cluster/cluster.hpp"
#include "etcdf_server/v3-grpc/services/kv/kv.hpp"
#include "etcdf_server/v3-grpc/services/lease/lease.hpp"
#include "etcdf_server/v3-grpc/services/maintenance/maintenance.hpp"
#include "etcdf_server/v3-grpc/services/watch/watch.hpp"
#include "ipaddress/ip-any-address.hpp"

namespace etcdf::server::v3_grpc {

void start_grpcserver(const ipaddress::ip_address &host, const uint16_t &port) {
    GRPCKVService kvService;
    GRPCWatchService watchService;
    GRPCLeaseService leaseService;
    GRPCMaintenanceService maintenanceService;
    GRPCAuthService authService;
    GRPCClusterService clusterService;
    std::string address = std::format("{}:{}", host.to_string(), port);
    grpc::ServerBuilder builder;
    builder.RegisterService(&kvService);
    builder.RegisterService(&watchService);
    builder.RegisterService(&leaseService);
    builder.RegisterService(&maintenanceService);
    builder.RegisterService(&authService);
    builder.RegisterService(&clusterService);
    builder.AddListeningPort(address, grpc::InsecureServerCredentials());
    const auto &server = builder.BuildAndStart();
    std::cout << "Server listening on " << address << std::endl;
    server->Wait();
};
};  // namespace etcdf::server::v3_grpc
