#pragma once

#include <grpcpp/server_context.h>
#include <grpcpp/support/status.h>
#include <grpcpp/support/sync_stream.h>
#include <string>
#include <unordered_map>

#include "src/etcdf_protobuf/rpc.grpc.pb.h"
#include "src/etcdf_protobuf/rpc.pb.h"

namespace etcdf::server::v3_grpc {
struct StoreValue {
    unsigned int revision;
    std::string payload;
};
extern std::unordered_map<std::string, StoreValue> store;
class GRPCKVService final : public etcdserverpb::KV::Service {
    ::grpc::Status Range(::grpc::ServerContext *context,
                         const ::etcdserverpb::RangeRequest *request,
                         ::etcdserverpb::RangeResponse *response) override;
    ::grpc::Status Put(::grpc::ServerContext *context,
                       const ::etcdserverpb::PutRequest *request,
                       ::etcdserverpb::PutResponse *response) override;
    ::grpc::Status DeleteRange(
        ::grpc::ServerContext *context,
        const ::etcdserverpb::DeleteRangeRequest *request,
        ::etcdserverpb::DeleteRangeResponse *response) override;
    ::grpc::Status Txn(::grpc::ServerContext *context,
                       const ::etcdserverpb::TxnRequest *request,
                       ::etcdserverpb::TxnResponse *response) override;
    ::grpc::Status Compact(
        ::grpc::ServerContext *context,
        const ::etcdserverpb::CompactionRequest *request,
        ::etcdserverpb::CompactionResponse *response) override;
};
};  // namespace etcdf::server::v3_grpc
