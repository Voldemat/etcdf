#include "./etcdf_cli.hpp"

#include <CLI/App.hpp>
#include <CLI/Error.hpp>
#include <CLI/Option.hpp>
#include <CLI/Validators.hpp>
#include <filesystem>
#include <format>
#include <fstream>
#include <iostream>
#include <ipaddress/ipaddress.hpp>
#include <memory>
#include <stdexcept>
#include <string>

#include "config.hpp"
#include "etcdf_server/launcher/launcher.hpp"

namespace etcdf::cli {
std::unique_ptr<CLI::App> createCLIApp() noexcept {
    std::unique_ptr<CLI::App> app = std::make_unique<CLI::App>("Etcdf");
    auto config_file_option = std::make_shared<std::string>();
    app->add_option("--config-file", *config_file_option,
                    "Path to the server configuration file. Note that if a "
                    "configuration file is provided, other command line flags "
                    "and environment variables will be ignored.");
    app->set_version_flag(
        "--version", std::format("etcdf Version: {}\nGit SHA: {}",
                                 config::ETCDF_VERSION, config::ETCDF_GIT_SHA));
    app->callback([config_file_option]() {
        try {
            const auto &config_filepath =
                std::filesystem::path(*config_file_option);
            if (!std::filesystem::exists(config_filepath)) {
                throw std::runtime_error(std::format("{} file does not exist",
                                                     config_filepath.string()));
            };
            std::ifstream config_file(config_filepath);
            const auto &server_config = config::config_from_file(config_file);
            etcdf::server::launcher::start_both_servers(server_config);
        } catch (const std::runtime_error &error) {
            std::cerr << error.what() << std::endl;
            throw CLI::RuntimeError(1);
        };
    });
    return app;
};
};  // namespace etcdf::cli
