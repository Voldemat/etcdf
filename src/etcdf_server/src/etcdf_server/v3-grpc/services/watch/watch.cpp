#include "./watch.hpp"

#include <grpcpp/server_context.h>
#include <grpcpp/support/status.h>
#include <grpcpp/support/sync_stream.h>

#include <cstdint>
#include <format>
#include <iostream>
#include <limits>
#include <random>
#include <unordered_map>

#include "src/etcdf_protobuf/rpc.pb.h"

namespace etcdf::server::v3_grpc {
std::unordered_map<void *, uint64_t> watch_ids = {};
uint64_t generate_watch_id() {
    std::random_device dev;
    std::ranlux48_base rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist6(
        std::numeric_limits<uint64_t>::min(),
        std::numeric_limits<unsigned int>::max());

    return dist6(rng);
};

::grpc::Status GRPCWatchService::Watch(
    ::grpc::ServerContext *context,
    ::grpc::ServerReaderWriter< ::etcdserverpb::WatchResponse,
                                ::etcdserverpb::WatchRequest> *stream) {
    etcdserverpb::WatchRequest request;
    while (stream->Read(&request)) {
        switch (request.request_union_case()) {
            case etcdserverpb::WatchRequest::RequestUnionCase::kCreateRequest: {
                const auto &createRequest = request.create_request();
                std::cout << std::format(
                                 "create request. key: {}, range_end: {}, "
                                 "start_revision: {}, progress_notify: {}, "
                                 "prev_kv: {}, watch_id: {}, fragment: {}",
                                 createRequest.key(), createRequest.range_end(),
                                 createRequest.start_revision(),
                                 createRequest.progress_notify(),
                                 createRequest.prev_kv(),
                                 createRequest.watch_id(),
                                 createRequest.fragment())
                          << std::endl;
                const auto& watch_id = generate_watch_id();
                watch_ids[(void*)stream] = watch_id;
                break;
            };
            case etcdserverpb::WatchRequest::RequestUnionCase::kCancelRequest: {
                const auto &cancelRequest = request.cancel_request();
            };
            case etcdserverpb::WatchRequest::RequestUnionCase::
                kProgressRequest: {
                const auto &progressRequest = request.progress_request();
            };
            case etcdserverpb::WatchRequest::RequestUnionCase::
                REQUEST_UNION_NOT_SET: {
                std::cout << "Warning: Encountered empty union in "
                             "etcdserverpb::WatchRequest"
                          << std::endl;
                break;
            };
        };
    };
    return grpc::Status::OK;
};
};  // namespace etcdf::server::v3_grpc
