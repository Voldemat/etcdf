#include "./grpc_server_handle.hpp"

#include <grpcpp/server.h>
#include <grpcpp/server_builder.h>

#include <memory>

namespace etcdf::server::v3_grpc {
GRPCServerHandle::GRPCServerHandle() {
    builder = std::make_unique<grpc::ServerBuilder>();
};
void GRPCServerHandle::run() {
    runningServer = builder->BuildAndStart();
    runningServer.value()->Wait();
};
void GRPCServerHandle::stop() {
    if (runningServer.has_value()) {
        runningServer.value()->Shutdown();
    };
};
};  // namespace etcdf::server::v3_grpc
