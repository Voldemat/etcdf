#pragma once

#include <grpcpp/server_context.h>
#include <grpcpp/support/status.h>
#include <grpcpp/support/sync_stream.h>

#include "src/etcdf_protobuf/rpc.grpc.pb.h"
#include "src/etcdf_protobuf/rpc.pb.h"

namespace etcdf::server::v3_grpc {

class GRPCWatchService final : public etcdserverpb::Watch::Service {
    ::grpc::Status Watch(
        ::grpc::ServerContext *context,
        ::grpc::ServerReaderWriter< ::etcdserverpb::WatchResponse,
                                    ::etcdserverpb::WatchRequest> *stream)
        override;
};
};  // namespace etcdf::server::v3_grpc
