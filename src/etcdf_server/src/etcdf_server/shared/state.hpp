#pragma once

#include <atomic>
#include <memory>
#include <optional>

#include "./server_handle.hpp"

namespace etcdf::server::shared {
class State {
    std::atomic<bool> should_stop = false;
    void shutdown_handle(
        const std::optional<std::weak_ptr<shared::ServerHandle>> &handle);

public:
    std::optional<std::weak_ptr<shared::ServerHandle>> httpserver_handle;
    std::optional<std::weak_ptr<shared::ServerHandle>> grpcserver_handle;
    void initialize_shutdown();
    void wait_for_shutdown_signal();
    void shutdown();
};
static_assert(std::atomic<bool>::is_always_lock_free);
};  // namespace etcdf::server::shared
