include(FetchContent)
set(protobuf_INSTALL OFF CACHE INTERNAL "")
set(protobuf_BUILD_TESTS OFF CACHE INTERNAL "")
set(protobuf_BUILD_CONFORMANCE OFF CACHE INTERNAL "")
set(protobuf_BUILD_EXAMPLES OFF CACHE INTERNAL "")
set(protobuf_BUILD_PROTOBUF_BINARIES ON CACHE INTERNAL "")
set(protobuf_BUILD_PROTOC_BINARIES ON CACHE INTERNAL "")
set(protobuf_BUILD_LIBPROTOC ON CACHE INTERNAL "")
set(protobuf_BUILD_LIBUPB OFF CACHE INTERNAL "")
set(protobuf_DISABLE_RTTI ON CACHE INTERNAL "")
set(protobuf_TEST_XML_OUTDIR "" CACHE INTERNAL "")
set(protobuf_ALLOW_CCACHE OFF CACHE INTERNAL "")
set(protobuf_FORCE_FETCH_DEPENDENCIES OFF CACHE INTERNAL "")
set(protobuf_LOCAL_DEPENDENCIES_ONLY ON CACHE INTERNAL "")
set(protobuf_JSONCPP_PROVIDER "package" CACHE INTERNAL "")
set(protobuf_ABSL_PROVIDER "package" CACHE INTERNAL "")
set(protobuf_BUILD_TESTS OFF CACHE INTERNAL "")
FetchContent_Declare(
    protobuf
    GIT_REPOSITORY https://github.com/protocolbuffers/protobuf.git
    GIT_TAG        v3.28.1
    SOURCE_SUBDIR  cmake
    FIND_PACKAGE_ARGS NAMES protobuf
)
FetchContent_MakeAvailable(protobuf)
include(FindProtobuf)
find_package(protobuf CONFIG REQUIRED)
