#pragma once

#include <grpcpp/server_builder.h>

#include <memory>
#include <optional>

#include "./services/container.hpp"
#include "etcdf_server/shared/server_handle.hpp"

namespace etcdf::server::v3_grpc {
class GRPCServerHandle : public shared::ServerHandle {
private:
    std::optional<std::unique_ptr<grpc::Server>> runningServer;

public:
    ServicesContainer servicesContainer;
    std::unique_ptr<grpc::ServerBuilder> builder;
    explicit GRPCServerHandle();
    void run() override;
    void stop() override;
};
};  // namespace etcdf::server::v3_grpc
