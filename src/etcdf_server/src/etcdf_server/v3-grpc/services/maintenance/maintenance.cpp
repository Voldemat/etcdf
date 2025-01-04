#include "./maintenance.hpp"

#include <grpcpp/server_context.h>
#include <grpcpp/support/status.h>

#include "src/etcdf_protobuf/rpc.pb.h"

namespace etcdf::server::v3_grpc {
::grpc::Status GRPCMaintenanceService::Alarm(
    ::grpc::ServerContext *context, const ::etcdserverpb::AlarmRequest *request,
    ::etcdserverpb::AlarmResponse *response) {
    return grpc::Status::OK;
};
::grpc::Status GRPCMaintenanceService::Downgrade(
    ::grpc::ServerContext *context,
    const ::etcdserverpb::DowngradeRequest *request,
    ::etcdserverpb::DowngradeResponse *response) {
    return grpc::Status::OK;
};
::grpc::Status GRPCMaintenanceService::Status(
    ::grpc::ServerContext *context,
    const ::etcdserverpb::StatusRequest *request,
    ::etcdserverpb::StatusResponse *response) {
    response->set_version("0.0.1");
    response->set_dbsize(100);
    response->set_leader(1);
    response->set_raftterm(1);
    response->set_raftindex(1);
    response->set_allocated_header(new etcdserverpb::ResponseHeader());
    return grpc::Status::OK;
};
::grpc::Status GRPCMaintenanceService::Defragment(
    ::grpc::ServerContext *context,
    const ::etcdserverpb::DefragmentRequest *request,
    ::etcdserverpb::DefragmentResponse *response) {
    return grpc::Status::OK;
};
::grpc::Status GRPCMaintenanceService::Hash(
    ::grpc::ServerContext *context, const ::etcdserverpb::HashRequest *request,
    ::etcdserverpb::HashResponse *response) {
    return grpc::Status::OK;
};
::grpc::Status GRPCMaintenanceService::HashKV(
    ::grpc::ServerContext *context,
    const ::etcdserverpb::HashKVRequest *request,
    ::etcdserverpb::HashKVResponse *response) {
    return grpc::Status::OK;
};
::grpc::Status GRPCMaintenanceService::Snapshot(
    ::grpc::ServerContext *context,
    const ::etcdserverpb::SnapshotRequest *request,
    ::grpc::ServerWriter< ::etcdserverpb::SnapshotResponse> *writer) {
    return grpc::Status::OK;
};
::grpc::Status GRPCMaintenanceService::MoveLeader(
    ::grpc::ServerContext *context,
    const ::etcdserverpb::MoveLeaderRequest *request,
    ::etcdserverpb::MoveLeaderResponse *response) {
    return grpc::Status::OK;
};
};  // namespace etcdf::server::v3_grpc
