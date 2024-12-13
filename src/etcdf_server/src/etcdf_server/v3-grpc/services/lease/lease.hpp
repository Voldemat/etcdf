#pragma once

#include <grpcpp/server_context.h>
#include <grpcpp/support/status.h>
#include <grpcpp/support/sync_stream.h>

#include "src/etcdf_protobuf/rpc.grpc.pb.h"
#include "src/etcdf_protobuf/rpc.pb.h"

namespace etcdf::server::v3_grpc {

class GRPCLeaseService final : public etcdserverpb::Lease::Service {
    ::grpc::Status LeaseGrant(
        ::grpc::ServerContext *context,
        const ::etcdserverpb::LeaseGrantRequest *request,
        ::etcdserverpb::LeaseGrantResponse *response) override;
    ::grpc::Status LeaseLeases(
        ::grpc::ServerContext *context,
        const ::etcdserverpb::LeaseLeasesRequest *request,
        ::etcdserverpb::LeaseLeasesResponse *response) override;
    ::grpc::Status LeaseRevoke(
        ::grpc::ServerContext *context,
        const ::etcdserverpb::LeaseRevokeRequest *request,
        ::etcdserverpb::LeaseRevokeResponse *response) override;
    ::grpc::Status LeaseTimeToLive(
        ::grpc::ServerContext *context,
        const ::etcdserverpb::LeaseTimeToLiveRequest *request,
        ::etcdserverpb::LeaseTimeToLiveResponse *response) override;
    ::grpc::Status LeaseKeepAlive(
        ::grpc::ServerContext *context,
        ::grpc::ServerReaderWriter< ::etcdserverpb::LeaseKeepAliveResponse,
                                    ::etcdserverpb::LeaseKeepAliveRequest>
            *stream) override;
};
};  // namespace etcdf::server::v3_grpc
