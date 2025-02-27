#include "./server.hpp"

#include <google/protobuf/empty.pb.h>
#include <grpc/grpc.h>
#include <grpcpp/grpcpp.h>
#include <grpcpp/security/credentials.h>
#include <grpcpp/security/server_credentials.h>
#include <grpcpp/support/interceptor.h>
#include <grpcpp/support/server_interceptor.h>
#include <grpcpp/support/status.h>
#include <grpcpp/support/sync_stream.h>

#include <cstddef>
#include <fstream>
#include <iostream>
#include <ipaddress/ip-address-base.hpp>
#include <memory>
#include <sstream>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

#include "./config_utils.hpp"
#include "./logging_interceptor.hpp"
#include "etcdf_server/shared/config.hpp"
#include "etcdf_server/shared/server_handle.hpp"
#include "etcdf_server/v3-grpc/base64.hpp"
#include "etcdf_server/v3-grpc/grpc_server_handle.hpp"
#include "etcdf_server/v3-grpc/services/kv/kv.hpp"
#include "libcxx-polyfills/concat_views.hpp"

namespace etcdf::server::v3_grpc {

std::shared_ptr<shared::ServerHandle> create_grpcserver(
    const shared::Config &config) {
    const auto &handle = std::make_shared<GRPCServerHandle>();
    grpc::ServerBuilder* builder = handle->builder.get();
    auto &services = handle->servicesContainer;
    grpc::ServerBuilder check;
    grpc::ServerBuilder* pointer = &check;
    pointer->RegisterService(&services.kvService);
    builder->RegisterService(&services.kvService);
    builder->RegisterService(&services.watchService);
    builder->RegisterService(&services.leaseService);
    builder->RegisterService(&services.maintenanceService);
    builder->RegisterService(&services.authService);
    builder->RegisterService(&services.clusterService);
    {
        std::ifstream dumpFile("./tmp/data3.txt");
        std::string line;
        while (std::getline(dumpFile, line)) {
            std::stringstream ss(line);
            std::string key;
            std::getline(ss, key, ':');
            std::string value;
            std::getline(ss, value, ':');
            const auto &parsedKeyBytes = base64_decode(key);
            const auto &parsedValueBytes = base64_decode(value);
            std::string parsedKey(parsedKeyBytes.begin(), parsedKeyBytes.end());
            std::string parsedValue(parsedValueBytes.begin(),
                                    parsedValueBytes.end());
            store[parsedKey] = {
                .revision = 1,
                .payload = parsedValue,
            };
        }
    }
    for (const auto &listener :
         std::views::concat(config.endpoints.grpc, config.endpoints.http)) {
        const auto &listenAddr = listenAddrFromEndpoint(listener);
        const auto &creds = mapTLSContextToGrpcCreds(listener.tlsContext);
        builder->AddListeningPort(listenAddr, creds);
        std::cout << "Server listening on: " << listenAddr << std::endl;
    };
    std::vector<GRPCFactory> factories;
    factories.push_back(std::make_unique<LoggingInterceptorFactory>());
    builder->experimental().SetInterceptorCreators(std::move(factories));
    return handle;
};
};  // namespace etcdf::server::v3_grpc
