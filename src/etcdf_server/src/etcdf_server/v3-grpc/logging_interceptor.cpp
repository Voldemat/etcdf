#include "./logging_interceptor.hpp"

#include <grpcpp/support/interceptor.h>
#include <grpcpp/support/server_interceptor.h>

#include <format>
#include <iostream>
#include <string>

namespace etcdf::server::v3_grpc {
LoggingInterceptor::LoggingInterceptor(
    grpc::experimental::ServerRpcInfo *info) {
    const std::string method = info->method();
    if (method == "unknown") {
        std::cout << "Unimplemented Rpc called" << std::endl;
        return;
    }
    std::cout << std::format("Rpc called: {}", method) << std::endl;
};

void LoggingInterceptor::Intercept(
    grpc::experimental::InterceptorBatchMethods *methods) {
    methods->Proceed();
};

LoggingInterceptor::Interceptor *
LoggingInterceptorFactory::CreateServerInterceptor(
    grpc::experimental::ServerRpcInfo *info) {
    return new LoggingInterceptor(info);
};
};  // namespace etcdf::server::v3_grpc
