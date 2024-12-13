#pragma once

#include <grpcpp/server_context.h>
#include <grpcpp/support/status.h>
#include <grpcpp/support/sync_stream.h>

#include "src/etcdf_protobuf/rpc.grpc.pb.h"
#include "src/etcdf_protobuf/rpc.pb.h"

namespace etcdf::server::v3_grpc {

class GRPCClusterService final : public etcdserverpb::Cluster::Service {
    ::grpc::Status MemberAdd(::grpc::ServerContext *context, const ::etcdserverpb::MemberAddRequest *request, ::etcdserverpb::MemberAddResponse *response) override;
    ::grpc::Status MemberList(::grpc::ServerContext *context, const ::etcdserverpb::MemberListRequest *request, ::etcdserverpb::MemberListResponse *response) override;
    ::grpc::Status MemberRemove(::grpc::ServerContext *context, const ::etcdserverpb::MemberRemoveRequest *request, ::etcdserverpb::MemberRemoveResponse *response) override;
    ::grpc::Status MemberUpdate(::grpc::ServerContext *context, const ::etcdserverpb::MemberUpdateRequest *request, ::etcdserverpb::MemberUpdateResponse *response) override;
    ::grpc::Status MemberPromote(::grpc::ServerContext *context, const ::etcdserverpb::MemberPromoteRequest *request, ::etcdserverpb::MemberPromoteResponse *response) override;
};
};  // namespace etcdf::server::v3_grpc
