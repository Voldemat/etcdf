#include "./server.hpp"

#include <google/protobuf/empty.pb.h>
#include <grpcpp/grpcpp.h>
#include <grpcpp/security/credentials.h>
#include <grpcpp/security/server_credentials.h>
#include <grpcpp/support/status.h>

#include <cstdint>
#include <format>
#include <iostream>
#include <memory>
#include <string>

#include "ipaddress/ip-any-address.hpp"
#include "src/etcdf_protobuf/test.grpc.pb.h"
#include "src/etcdf_protobuf/test.pb.h"

class Check final : public Test::Service {
    ::grpc::Status Put(::grpc::ServerContext *context,
                       const ::PutRequest *request,
                       ::google::protobuf::Empty *response) override {
        response->New();
        return grpc::Status::OK;
    };
};
namespace etcdf::server::v3_grpc {
void start_grpcserver(const ipaddress::ip_address &host, const uint16_t &port) {
    Check check;
    std::string address = std::format("{}:{}", host.to_string(), port);
    grpc::ServerBuilder builder;
    builder.RegisterService(&check);
    builder.AddListeningPort(address, grpc::InsecureServerCredentials());
    const auto& server = builder.BuildAndStart();
    std::cout << "Server listening on " << address << std::endl;
    server->Wait();
};
};  // namespace etcdf::server::v3_grpc
