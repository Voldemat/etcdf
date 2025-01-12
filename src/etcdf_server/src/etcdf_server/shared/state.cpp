#include "./state.hpp"

#include <memory>
#include <optional>

#include "etcdf_server/shared/server_handle.hpp"

namespace etcdf::server::shared {
void State::initialize_shutdown() {
    should_stop = true;
    should_stop.notify_all();
};

void State::wait_for_shutdown_signal() { should_stop.wait(false); };

void State::shutdown_handle(
    const std::optional<std::weak_ptr<shared::ServerHandle>> &handle) {
    if (handle.has_value()) {
        const auto &weak_ptr = handle.value();
        if (!weak_ptr.expired()) {
            weak_ptr.lock()->stop();
        };
    };
};
void State::shutdown() {
    shutdown_handle(httpserver_handle);
    shutdown_handle(grpcserver_handle);
};
};  // namespace etcdf::server::shared
