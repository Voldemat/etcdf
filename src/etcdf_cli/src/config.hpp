#pragma once

#include <fstream>

#include "etcdf_server/shared/config.hpp"

namespace etcdf::cli::config {
extern const char *ETCDF_VERSION;
extern const char *ETCDF_GIT_SHA;

etcdf::server::shared::Config config_from_file(std::ifstream &file);
};  // namespace etcdf::cli::config
