#include "./config_utils.hpp"

#include <grpcpp/security/server_credentials.h>

#include <format>
#include <fstream>
#include <ipaddress/ip-address-base.hpp>
#include <iterator>
#include <memory>
#include <optional>
#include <string>

#include "etcdf_server/shared/config.hpp"

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

std::string listenAddrFromEndpoint(const shared::Endpoint &endpoint) {
    switch (endpoint.ipAddress.version()) {
        case ipaddress::ip_version::V4: {
            return std::format("{}:{}", endpoint.ipAddress.to_string(),
                               endpoint.port);
        }
        case ipaddress::ip_version::V6: {
            return std::format("[{}]:{}", endpoint.ipAddress.to_string(),
                               endpoint.port);
        }
    };
};

std::shared_ptr<grpc::ServerCredentials> mapTLSContextToGrpcCreds(
    const std::optional<std::shared_ptr<shared::TLSContext>> &context) {
    return context.has_value()
               ? tlsContextToSslServerCredentialsOptions(*context.value())
               : grpc::InsecureServerCredentials();
};
};  // namespace etcdf::server::v3_grpc
