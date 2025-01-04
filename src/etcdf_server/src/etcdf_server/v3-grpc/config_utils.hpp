#pragma once

#include <grpcpp/security/server_credentials.h>
#include <grpcpp/support/server_interceptor.h>

#include <ipaddress/ip-address-base.hpp>
#include <memory>
#include <optional>
#include <string>

#include "etcdf_server/shared/config.hpp"

namespace etcdf::server::v3_grpc {
using GRPCFactory =
    std::unique_ptr<grpc::experimental::ServerInterceptorFactoryInterface>;
std::shared_ptr<grpc::ServerCredentials>
tlsContextToSslServerCredentialsOptions(const shared::TLSContext &context);

std::shared_ptr<grpc::ServerCredentials> mapTLSContextToGrpcCreds(
    const std::optional<std::shared_ptr<shared::TLSContext>> &context);

std::string listenAddrFromEndpoint(const shared::Endpoint &endpoint);
};  // namespace etcdf::server::v3_grpc
