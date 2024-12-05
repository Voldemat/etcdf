#pragma once

#include <CLI/App.hpp>
#include <memory>

std::unique_ptr<CLI::App> createCLIApp() noexcept;
