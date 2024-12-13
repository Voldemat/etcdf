#include "./cluster.hpp"

#include <grpcpp/server_context.h>
#include <grpcpp/support/status.h>
#include <grpcpp/support/sync_stream.h>

#include "src/etcdf_protobuf/rpc.pb.h"

namespace etcdf::server::v3_grpc {
::grpc::Status GRPCClusterService::MemberAdd(
    ::grpc::ServerContext *context,
    const ::etcdserverpb::MemberAddRequest *request,
    ::etcdserverpb::MemberAddResponse *response) {
    return grpc::Status::OK;
};
::grpc::Status GRPCClusterService::MemberList(
    ::grpc::ServerContext *context,
    const ::etcdserverpb::MemberListRequest *request,
    ::etcdserverpb::MemberListResponse *response) {
    return grpc::Status::OK;
};
::grpc::Status GRPCClusterService::MemberRemove(
    ::grpc::ServerContext *context,
    const ::etcdserverpb::MemberRemoveRequest *request,
    ::etcdserverpb::MemberRemoveResponse *response) {
    return grpc::Status::OK;
};
::grpc::Status GRPCClusterService::MemberUpdate(
    ::grpc::ServerContext *context,
    const ::etcdserverpb::MemberUpdateRequest *request,
    ::etcdserverpb::MemberUpdateResponse *response) {
    return grpc::Status::OK;
};
::grpc::Status GRPCClusterService::MemberPromote(
    ::grpc::ServerContext *context,
    const ::etcdserverpb::MemberPromoteRequest *request,
    ::etcdserverpb::MemberPromoteResponse *response) {
    return grpc::Status::OK;
};
};  // namespace etcdf::server::v3_grpc
