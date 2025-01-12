#include "./launcher.hpp"

#include <pthread.h>

#include <csignal>
#include <optional>
#include <thread>

#include "etcdf_server/shared/config.hpp"
#include "etcdf_server/shared/server_handle.hpp"
#include "etcdf_server/shared/state.hpp"
#include "etcdf_server/v2-http/server.hpp"
#include "etcdf_server/v3-grpc/server.hpp"

namespace etcdf::server::launcher {

void server_handle_runner(shared::ServerHandle *server) {
    server->run();
};

void start_both_servers(const shared::Config &config, shared::State &state) {
    const auto &httpserver = etcdf::server::v2_http::create_httpserver(config);
    state.httpserver_handle = httpserver;
    std::thread http_thread(server_handle_runner, httpserver.get());
    const auto &grpcserver = etcdf::server::v3_grpc::create_grpcserver(config);
    state.grpcserver_handle = grpcserver;
    std::thread grpc_thread(server_handle_runner, grpcserver.get());
    std::thread signal_thread(
        [](shared::State *s) {
            s->wait_for_shutdown_signal();
            s->shutdown();
        },
        &state);
    signal_thread.join();
    http_thread.join();
    grpc_thread.join();
};
};  // namespace etcdf::server::launcher
