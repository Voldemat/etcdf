#pragma once

#include <grpcpp/server_context.h>
#include <grpcpp/support/status.h>
#include <grpcpp/support/sync_stream.h>

#include "src/etcdf_protobuf/rpc.grpc.pb.h"
#include "src/etcdf_protobuf/rpc.pb.h"

namespace etcdf::server::v3_grpc {
class GRPCMaintenanceService final : public etcdserverpb::Maintenance::Service {
    ::grpc::Status Alarm(::grpc::ServerContext *context, const ::etcdserverpb::AlarmRequest *request, ::etcdserverpb::AlarmResponse *response) override;
    ::grpc::Status Downgrade(::grpc::ServerContext *context, const ::etcdserverpb::DowngradeRequest *request, ::etcdserverpb::DowngradeResponse *response) override;
    ::grpc::Status Status(::grpc::ServerContext *context, const ::etcdserverpb::StatusRequest *request, ::etcdserverpb::StatusResponse *response) override;
    ::grpc::Status Defragment(::grpc::ServerContext *context, const ::etcdserverpb::DefragmentRequest *request, ::etcdserverpb::DefragmentResponse *response) override;
    ::grpc::Status Hash(::grpc::ServerContext *context, const ::etcdserverpb::HashRequest *request, ::etcdserverpb::HashResponse *response) override;
    ::grpc::Status HashKV(::grpc::ServerContext *context, const ::etcdserverpb::HashKVRequest *request, ::etcdserverpb::HashKVResponse *response) override;
    ::grpc::Status Snapshot(::grpc::ServerContext *context, const ::etcdserverpb::SnapshotRequest *request, ::grpc::ServerWriter< ::etcdserverpb::SnapshotResponse> *writer) override;
    ::grpc::Status MoveLeader(::grpc::ServerContext *context, const ::etcdserverpb::MoveLeaderRequest *request, ::etcdserverpb::MoveLeaderResponse *response) override;
};
};  // namespace etcdf::server::v3_grpc
