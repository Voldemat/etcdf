#include "./kv.hpp"

#include <grpcpp/server_context.h>
#include <grpcpp/support/status.h>
#include <format>
#include <iostream>

#include "src/etcdf_protobuf/rpc.pb.h"

namespace etcdf::server::v3_grpc {
::grpc::Status GRPCKVService::Range(::grpc::ServerContext *context,
                                    const ::etcdserverpb::RangeRequest *request,
                                    ::etcdserverpb::RangeResponse *response) {
    response->set_allocated_header(new etcdserverpb::ResponseHeader());
    response->set_more(false);
    response->set_count(0);
    std::cout << std::format("Range. Key: {}", request->key()) << std::endl;
    return grpc::Status::OK;
};

::grpc::Status GRPCKVService::Put(::grpc::ServerContext *context,
                                  const ::etcdserverpb::PutRequest *request,
                                  ::etcdserverpb::PutResponse *response) {
    return grpc::Status::OK;
};
::grpc::Status GRPCKVService::DeleteRange(
    ::grpc::ServerContext *context,
    const ::etcdserverpb::DeleteRangeRequest *request,
    ::etcdserverpb::DeleteRangeResponse *response) {
    return grpc::Status::OK;
};
::grpc::Status GRPCKVService::Txn(::grpc::ServerContext *context,
                                  const ::etcdserverpb::TxnRequest *request,
                                  ::etcdserverpb::TxnResponse *response) {
    return grpc::Status::OK;
};
::grpc::Status GRPCKVService::Compact(
    ::grpc::ServerContext *context,
    const ::etcdserverpb::CompactionRequest *request,
    ::etcdserverpb::CompactionResponse *response) {
    return grpc::Status::OK;
};
};  // namespace etcdf::server::v3_grpc
