#include "./etcdf_cli.hpp"

#include <CLI/App.hpp>
#include <CLI/Error.hpp>
#include <CLI/Option.hpp>
#include <CLI/Validators.hpp>
#include <memory>


std::unique_ptr<CLI::App> createCLIApp() noexcept {
    std::unique_ptr<CLI::App> app = std::make_unique<CLI::App>("Etcdf");
    app->require_subcommand(1);
    return app;
};
