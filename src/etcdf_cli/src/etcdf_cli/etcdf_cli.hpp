#pragma once

#include <CLI/App.hpp>
#include <memory>

namespace etcdf::cli {
std::unique_ptr<CLI::App> createCLIApp() noexcept;
};
