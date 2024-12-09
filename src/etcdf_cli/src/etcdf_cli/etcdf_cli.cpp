#include "./etcdf_cli.hpp"

#include <CLI/App.hpp>
#include <CLI/Error.hpp>
#include <CLI/Option.hpp>
#include <CLI/Validators.hpp>
#include <ipaddress/ipaddress.hpp>
#include <memory>
#include <optional>
#include <string>

#include "etcdf_server/launcher/launcher.hpp"
#include "ipaddress/errors.hpp"
#include "ipaddress/ip-any-address.hpp"

namespace etcdf::cli {
auto host_validator = CLI::Validator(
    [](const std::string &input) {
        try {
            ipaddress::ip_address::parse(input);
            return "";
        } catch (const ipaddress::parse_error &error) {
            throw CLI::ValidationError(error.what());
        };
    },
    "", "host validator");
auto port_validator = CLI::Validator(
    [](const std::string &input) {
        if (input == "0") {
            throw CLI::ValidationError("Port cannot be 0");
        };
        return "";
    },
    "", "port validator");
std::unique_ptr<CLI::App> createCLIApp() noexcept {
    std::unique_ptr<CLI::App> app = std::make_unique<CLI::App>("Etcdf");
    auto http_host = std::make_shared<std::string>();
    app->add_option("--http-address", *http_host, "Http listening ip address")
        ->required()
        ->transform(host_validator);
    auto http_port = std::make_shared<unsigned short>();
    app->add_option("--http-port", *http_port, "Http listening port")
        ->required()
        ->transform(port_validator);
    auto grpc_host = std::make_shared<std::string>();
    app->add_option("--grpc-address", *grpc_host, "gRPC listening ip address")
        ->required()
        ->transform(host_validator);
    auto grpc_port = std::make_shared<unsigned short>();
    app->add_option("--grpc-port", *grpc_port, "gRPC listening port")
        ->required()
        ->transform(port_validator);
    app->callback([http_host, http_port, grpc_host, grpc_port]() {
        const auto &http_host_ip = ipaddress::ip_address::parse(*http_host);
        const auto &grpc_host_ip = ipaddress::ip_address::parse(*grpc_host);
        etcdf::server::launcher::start_both_servers(
            http_host_ip, *http_port, std::nullopt, grpc_host_ip, *grpc_port);
    });
    return app;
};
};  // namespace etcdf::cli
