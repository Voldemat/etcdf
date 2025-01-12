#include "./grpc_server_handle.hpp"

#include <grpcpp/server.h>

#include <memory>
#include <utility>

namespace etcdf::server::v3_grpc {
GRPCServerHandle::GRPCServerHandle(std::unique_ptr<grpc::Server> &&grpcServer)
    : grpcServer{ std::move(grpcServer) } {};
void GRPCServerHandle::run() { grpcServer->Wait(); };
void GRPCServerHandle::stop() { grpcServer->Shutdown(); };
};  // namespace etcdf::server::v3_grpc
