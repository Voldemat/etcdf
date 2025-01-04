#pragma once

#include <grpcpp/support/interceptor.h>
#include <grpcpp/support/server_interceptor.h>

namespace etcdf::server::v3_grpc {
class LoggingInterceptor final : public ::grpc::experimental::Interceptor {
public:
    explicit LoggingInterceptor(grpc::experimental::ServerRpcInfo *info);

    void Intercept(
        grpc::experimental::InterceptorBatchMethods *methods) override;
};

class LoggingInterceptorFactory
    : public grpc::experimental::ServerInterceptorFactoryInterface {
public:
    LoggingInterceptor::Interceptor *CreateServerInterceptor(
        grpc::experimental::ServerRpcInfo *info) override;
};
};  // namespace etcdf::server::v3_grpc
