#include "./lease.hpp"

#include <grpcpp/server_context.h>
#include <grpcpp/support/status.h>
#include <grpcpp/support/sync_stream.h>

#include "src/etcdf_protobuf/rpc.pb.h"

namespace etcdf::server::v3_grpc {
::grpc::Status GRPCLeaseService::LeaseGrant(
    ::grpc::ServerContext *context,
    const ::etcdserverpb::LeaseGrantRequest *request,
    ::etcdserverpb::LeaseGrantResponse *response) {
    return grpc::Status::OK;
};
::grpc::Status GRPCLeaseService::LeaseLeases(
    ::grpc::ServerContext *context,
    const ::etcdserverpb::LeaseLeasesRequest *request,
    ::etcdserverpb::LeaseLeasesResponse *response) {
    return grpc::Status::OK;
};
::grpc::Status GRPCLeaseService::LeaseRevoke(
    ::grpc::ServerContext *context,
    const ::etcdserverpb::LeaseRevokeRequest *request,
    ::etcdserverpb::LeaseRevokeResponse *response) {
    return grpc::Status::OK;
};
::grpc::Status GRPCLeaseService::LeaseTimeToLive(
    ::grpc::ServerContext *context,
    const ::etcdserverpb::LeaseTimeToLiveRequest *request,
    ::etcdserverpb::LeaseTimeToLiveResponse *response) {
    return grpc::Status::OK;
};
::grpc::Status GRPCLeaseService::LeaseKeepAlive(
    ::grpc::ServerContext *context,
    ::grpc::ServerReaderWriter< ::etcdserverpb::LeaseKeepAliveResponse,
                                ::etcdserverpb::LeaseKeepAliveRequest>
        *stream) {
    return grpc::Status::OK;
};
};  // namespace etcdf::server::v3_grpc
