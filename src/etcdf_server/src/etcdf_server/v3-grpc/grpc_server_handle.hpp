#pragma once

#include <grpcpp/server.h>

#include <memory>

#include "etcdf_server/shared/server_handle.hpp"

namespace etcdf::server::v3_grpc {
class GRPCServerHandle : public shared::ServerHandle {
private:
    std::unique_ptr<grpc::Server> grpcServer;

public:
    explicit GRPCServerHandle(std::unique_ptr<grpc::Server> &&grpcServer);
    void run() override;
    void stop() override;
};
};  // namespace etcdf::server::v3_grpc
