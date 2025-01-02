#include "./server.hpp"

#include <google/protobuf/empty.pb.h>
#include <grpcpp/grpcpp.h>
#include <grpcpp/security/credentials.h>
#include <grpcpp/security/server_credentials.h>
#include <grpcpp/support/status.h>
#include <grpcpp/support/sync_stream.h>

#include <format>
#include <fstream>
#include <iostream>
#include <ipaddress/ip-address-base.hpp>
#include <iterator>
#include <memory>
#include <string>
#include <vector>

#include "etcdf_server/shared/config.hpp"
#include "etcdf_server/v3-grpc/services/auth/auth.hpp"
#include "etcdf_server/v3-grpc/services/cluster/cluster.hpp"
#include "etcdf_server/v3-grpc/services/kv/kv.hpp"
#include "etcdf_server/v3-grpc/services/lease/lease.hpp"
#include "etcdf_server/v3-grpc/services/maintenance/maintenance.hpp"
#include "etcdf_server/v3-grpc/services/watch/watch.hpp"
#include "libcxx-polyfills/concat_views.hpp"

namespace etcdf::server::v3_grpc {

std::shared_ptr<grpc::ServerCredentials>
tlsContextToSslServerCredentialsOptions(const shared::TLSContext &context) {
    grpc::SslServerCredentialsOptions options;
    std::ifstream privateKeyFile(context.privateKeyPath);
    std::ifstream certFile(context.certPath);
    grpc::SslServerCredentialsOptions::PemKeyCertPair tlsPair = {
        .private_key =
            std::string(std::istreambuf_iterator<char>(privateKeyFile),
                        std::istreambuf_iterator<char>()),
        .cert_chain = std::string(std::istreambuf_iterator<char>(certFile),
                                  std::istreambuf_iterator<char>())
    };
    options.pem_key_cert_pairs = { tlsPair };
    if (context.caPath.has_value()) {
        std::ifstream caFile(context.caPath.value());
        options.pem_root_certs =
            std::string(std::istreambuf_iterator<char>(caFile),
                        std::istreambuf_iterator<char>());
    };
    return grpc::SslServerCredentials(options);
};

std::string listenAddrFromEndpoint(const shared::Endpoint& endpoint) {
    switch (endpoint.ip_address.version()) {
        case ipaddress::ip_version::V4: {
        return std::format(
            "{}:{}", endpoint.ip_address.to_string(), endpoint.port);
        }
        case ipaddress::ip_version::V6: {
        return std::format(
            "[{}]:{}", endpoint.ip_address.to_string(), endpoint.port);
        }
    };
};

void start_grpcserver(const shared::Config &config) {
    GRPCKVService kvService;
    GRPCWatchService watchService;
    GRPCLeaseService leaseService;
    GRPCMaintenanceService maintenanceService;
    GRPCAuthService authService;
    GRPCClusterService clusterService;
    grpc::ServerBuilder builder;
    builder.RegisterService(&kvService);
    builder.RegisterService(&watchService);
    builder.RegisterService(&leaseService);
    builder.RegisterService(&maintenanceService);
    builder.RegisterService(&authService);
    builder.RegisterService(&clusterService);
    for (const auto &listener : std::views::concat(
             config.listeners.peers.grpc, config.listeners.clients.grpc)) {
        grpc::SslServerCredentialsOptions options;
        std::shared_ptr<grpc::ServerCredentials> creds =
            listener.tlsContext.has_value()
                ? tlsContextToSslServerCredentialsOptions(
                      listener.tlsContext.value())
                : grpc::InsecureServerCredentials();
        const auto& listenAddr = listenAddrFromEndpoint(listener);
        builder.AddListeningPort(listenAddr, creds);
        std::cout << "Server listening on: " << listenAddr << std::endl;
    };
    const auto &server = builder.BuildAndStart();
    server->Wait();
};
};  // namespace etcdf::server::v3_grpc
