#pragma once

#include "etcdf_server/shared/config.hpp"

namespace etcdf::server::launcher {
void start_both_servers(const shared::Config &config);
};
