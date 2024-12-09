#include "./etcdf_cli.hpp"

#include <CLI/App.hpp>
#include <CLI/Error.hpp>
#include <CLI/Option.hpp>
#include <CLI/Validators.hpp>
#include <ipaddress/ipaddress.hpp>
#include <memory>
#include <optional>
#include <string>

#include "ipaddress/errors.hpp"
#include "ipaddress/ip-any-address.hpp"
#include "etcdf_server/v2-http/server.hpp"

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
    auto host = std::make_shared<std::string>();
    app->add_option("-a,--address", *host, "Listening ip address")
        ->required()
        ->transform(host_validator);
    auto port = std::make_shared<unsigned short>();
    app->add_option("-p,--port", *port, "Listening port")
        ->required()
        ->transform(port_validator);
    app->callback([host, port]() {
        const auto &host_ip = ipaddress::ip_address::parse(*host);
        etcdf::server::start_httpserver(host_ip, *port, std::nullopt);
    });
    return app;
};
};  // namespace etcdf::cli
