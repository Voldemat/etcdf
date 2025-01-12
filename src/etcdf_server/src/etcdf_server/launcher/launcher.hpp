#pragma once

#include "etcdf_server/shared/config.hpp"
#include "etcdf_server/shared/state.hpp"

namespace etcdf::server::launcher {
void start_both_servers(const shared::Config &config, shared::State &state);
};
