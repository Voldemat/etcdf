#include "./kv.hpp"

#include <grpcpp/server_context.h>
#include <grpcpp/support/status.h>

#include <cstring>
#include <format>
#include <iostream>
#include <magic_enum.hpp>
#include <ranges>
#include <string>
#include <unordered_map>

#include "src/etcdf_protobuf/kv.pb.h"
#include "src/etcdf_protobuf/rpc.pb.h"

namespace etcdf::server::v3_grpc {

bool calc_left(const std::string &left, const std::string &key) {
    return std::memcmp(key.data(), left.data(), left.size()) == 0;
};

bool calc_right(const std::string &right, const std::string &key) {
    return std::memcmp(right.data(), key.data(), key.size()) > 0;
};
std::unordered_map<std::string, std::string> store;

::grpc::Status GRPCKVService::Range(::grpc::ServerContext *context,
                                    const ::etcdserverpb::RangeRequest *request,
                                    ::etcdserverpb::RangeResponse *response) {
    const auto &header = new etcdserverpb::ResponseHeader();
    header->set_revision(1);
    header->set_member_id(1);
    header->set_raft_term(1);
    header->set_cluster_id(1);
    response->set_allocated_header(header);
    const auto &endKey = request->range_end();
    const auto &startKey = request->key();
    std::cout << std::format("Range. startKey: {}, endKey: {}", startKey,
                             endKey)
              << std::endl;
    response->set_more(false);
    response->set_count(0);
    if (endKey == "") {
        if (store.contains(startKey)) {
            response->set_more(false);
            response->set_count(1);
            const auto &keyValue = response->add_kvs();
            keyValue->set_key(startKey);
            keyValue->set_value(store.at(startKey));
            keyValue->set_version(3);
            keyValue->set_mod_revision(2);
            keyValue->set_create_revision(1);
        };
    } else {
        unsigned int count = 0;
        for (const auto &[key, value] : store) {
            bool left = calc_left(startKey, key);
            bool right = calc_right(endKey, key);
            if (left && right) {
                count++;
                const auto &keyValue = response->add_kvs();
                keyValue->set_key(key);
                if (!request->keys_only()) {
                    keyValue->set_value(store.at(key));
                };
                keyValue->set_version(3);
                keyValue->set_mod_revision(2);
                keyValue->set_create_revision(1);
            };
        };
        response->set_count(count);
    };
    return grpc::Status::OK;
};

::grpc::Status GRPCKVService::Put(::grpc::ServerContext *context,
                                  const ::etcdserverpb::PutRequest *request,
                                  ::etcdserverpb::PutResponse *response) {
    store[request->key()] = request->value();
    std::cout << std::format("Put. Key: {}, Value: {}, PrevKv: {}",
                             request->key(), request->value(),
                             request->prev_kv())
              << std::endl;
    return grpc::Status::OK;
};
::grpc::Status GRPCKVService::DeleteRange(
    ::grpc::ServerContext *context,
    const ::etcdserverpb::DeleteRangeRequest *request,
    ::etcdserverpb::DeleteRangeResponse *response) {
    const auto &endKey = request->range_end();
    const auto &startKey = request->key();
    std::cout << std::format(
                     "DeleteRange. startKey: {}, endKey: {}, prevKv: {}",
                     startKey, endKey, request->prev_kv())
              << std::endl;
    if (endKey == "") {
        store.erase(startKey);
        response->set_deleted(1);
    } else {
        unsigned int count = 0;
        for (const auto &key : store | std::views::keys) {
            bool left = calc_left(startKey, key);
            bool right = calc_right(endKey, key);
            if (left && right) {
                store.erase(key);
                count++;
            };
        };
        response->set_deleted(count);
    };
    return grpc::Status::OK;
};
::grpc::Status GRPCKVService::Txn(::grpc::ServerContext *context,
                                  const ::etcdserverpb::TxnRequest *request,
                                  ::etcdserverpb::TxnResponse *response) {
    for (const auto &compare : request->compare()) {
        std::cout << std::format(
                         "Compare. Key: {}, Value: {}, Result: {}, Target: {}",
                         compare.key(), compare.value(),
                         magic_enum::enum_name(compare.result()),
                         magic_enum::enum_name(compare.target()))
                  << std::endl;
    };
    response->set_succeeded(true);
    for (const auto &success : request->success()) {
        switch (success.request_case()) {
            case etcdserverpb::RequestOp::RequestCase::kRequestPut: {
                const auto &op = success.request_put();
                const auto &putResponse = new etcdserverpb::PutResponse();
                Put(context, &op, putResponse);
                const auto &responseOp = response->add_responses();
                responseOp->set_allocated_response_put(putResponse);
                break;
            };
            case etcdserverpb::RequestOp::RequestCase::kRequestRange: {
                const auto &op = success.request_range();
                const auto &rangeResponse = new etcdserverpb::RangeResponse();
                Range(context, &op, rangeResponse);
                const auto &responseOp = response->add_responses();
                responseOp->set_allocated_response_range(rangeResponse);
                break;
            };
            case etcdserverpb::RequestOp::RequestCase::kRequestDeleteRange: {
                const auto &op = success.request_delete_range();
                const auto &deleteRangeResponse =
                    new etcdserverpb::DeleteRangeResponse();
                DeleteRange(context, &op, deleteRangeResponse);
                const auto &responseOp = response->add_responses();
                responseOp->set_allocated_response_delete_range(
                    deleteRangeResponse);
                break;
            };
            case etcdserverpb::RequestOp::RequestCase::kRequestTxn: {
                const auto &op = success.request_txn();
                const auto &txnResponse = new etcdserverpb::TxnResponse();
                Txn(context, &op, txnResponse);
                const auto &responseOp = response->add_responses();
                responseOp->set_allocated_response_txn(txnResponse);
                break;
            };
            case etcdserverpb::RequestOp::RequestCase::REQUEST_NOT_SET: {
                std::cout << std::format("Request not set") << std::endl;
                break;
            };
        };
    };
    return grpc::Status::OK;
};
::grpc::Status GRPCKVService::Compact(
    ::grpc::ServerContext *context,
    const ::etcdserverpb::CompactionRequest *request,
    ::etcdserverpb::CompactionResponse *response) {
    return grpc::Status::OK;
};
};  // namespace etcdf::server::v3_grpc
