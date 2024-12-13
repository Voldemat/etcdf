#include "./watch.hpp"

#include <grpcpp/server_context.h>
#include <grpcpp/support/status.h>
#include <grpcpp/support/sync_stream.h>

#include "src/etcdf_protobuf/rpc.pb.h"

namespace etcdf::server::v3_grpc {
::grpc::Status GRPCWatchService::Watch(
    ::grpc::ServerContext *context,
    ::grpc::ServerReaderWriter< ::etcdserverpb::WatchResponse,
                                ::etcdserverpb::WatchRequest> *stream) {
    return grpc::Status::OK;
};
};  // namespace etcdf::server::v3_grpc
