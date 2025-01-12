#include "./launcher.hpp"
#include <pthread.h>
#include <atomic>
#include <csignal>
#include <iostream>
#include <optional>
#include <thread>

#include "etcdf_server/shared/config.hpp"
#include "etcdf_server/shared/server_handle.hpp"
#include "etcdf_server/v2-http/server.hpp"
#include "etcdf_server/v3-grpc/server.hpp"

namespace etcdf::server::launcher {

static volatile std::atomic<bool> should_stop = false;
static_assert(should_stop.is_always_lock_free);
static std::optional<shared::ServerHandle*> httpserver_handle;
static std::optional<shared::ServerHandle*> grpcserver_handle;

void signal_handler(int signal) {
    should_stop = true;
    should_stop.notify_all();
};

void signal_thread_main() {
    should_stop.wait(false);
    std::cout << "signal_handle is called" << std::endl;
    if (httpserver_handle.has_value()) {
        std::cout << "Stopping http server" << std::endl;
        httpserver_handle.value()->stop();
        std::cout << "Stopped http server" << std::endl;
    };
    if (grpcserver_handle.has_value()) {
        std::cout << "Stopping grpc server" << std::endl;
        grpcserver_handle.value()->stop();
        std::cout << "Stopped grpc server" << std::endl;
    };
};

void server_handle_runner(shared::ServerHandle* server) {
    server->run();
};

void start_both_servers(const shared::Config &config) {
    auto httpserver = etcdf::server::v2_http::create_httpserver(config);
    httpserver_handle = httpserver.get();
    std::thread http_thread(server_handle_runner, httpserver.get());
    auto grpcserver = etcdf::server::v3_grpc::create_grpcserver(config);
    grpcserver_handle = grpcserver.get();
    std::thread grpc_thread(server_handle_runner, grpcserver.get());
    std::thread signal_thread(signal_thread_main);
    std::signal(SIGINT, signal_handler);
    signal_thread.join();
    std::cout << "Signal thread joined" << std::endl;
    http_thread.join();
    std::cout << "http thread joined" << std::endl;
    grpc_thread.join();
    std::cout << "grpc thread joined" << std::endl;
    std::cout << "start_both_servers end" << std::endl;
};
};  // namespace etcdf::server::launcher
