include(FetchContent)
include("${CMAKE_CURRENT_LIST_DIR}/grpc-deps/absl.cmake")
include("${CMAKE_CURRENT_LIST_DIR}/grpc-deps/protobuf.cmake")
set(gRPC_INSTALL ON CACHE INTERNAL "")
set(gRPC_ZLIB_PROVIDER "package" CACHE INTERNAL "")
set(gRPC_PROTOBUF_PROVIDER "package" CACHE INTERNAL "")
set(gRPC_CARES_PROVIDER "package" CACHE INTERNAL "")
set(gRPC_SSL_PROVIDER "package" CACHE INTERNAL "")
set(gRPC_ABSL_PROVIDER "package" CACHE INTERNAL "")
set(gRPC_BENCHMARK_PROVIDER "package" CACHE INTERNAL "")
set(GRPC_BUILD_ENABLE_CCACHE OFF CACHE INTERNAL "")
set(GRPC_RE2_PROVIDER "package" CACHE INTERNAL "")
FetchContent_Declare(
    gRPC
    GIT_REPOSITORY https://github.com/grpc/grpc
    GIT_TAG v1.68.2
    GIT_SUBMODULES
    GIT_SHALLOW TRUE
    FIND_PACKAGE_ARGS NAMES gRPC
)
FetchContent_MakeAvailable(gRPC)
get_target_property(
    ABSL_BASE_INTERNAL_INCLUDE_DIRS
    absl::base_internal
    INTERFACE_INCLUDE_DIRECTORIES
)
get_target_property(
    PROTOBUF_INCLUDE_DIRS
    libprotobuf
    INTERFACE_INCLUDE_DIRECTORIES
)
target_include_directories(
    grpc
    PRIVATE ${ABSL_BASE_INTERNAL_INCLUDE_DIRS}
    PRIVATE ${PROTOBUF_INCLUDE_DIRS}
)
target_include_directories(
    grpc_plugin_support
    PRIVATE ${ABSL_BASE_INTERNAL_INCLUDE_DIRS}
    PRIVATE ${PROTOBUF_INCLUDE_DIRS}
)
