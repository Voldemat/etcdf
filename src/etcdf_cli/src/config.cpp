#include "./config.hpp"

#include <yaml-cpp/node/node.h>
#include <yaml-cpp/node/parse.h>

#include <fstream>
#include <stdexcept>

#include "etcdf_server/shared/config.hpp"

namespace etcdf::cli::config {
etcdf::server::shared::Config config_from_file(std::ifstream &file) {
    etcdf::server::shared::Config config;
    const auto &node = YAML::Load(file);
    if (!node.IsMap()) {
        throw std::runtime_error("Config must be a yaml map");
    };
    return config;
};
};  // namespace etcdf::cli::config
