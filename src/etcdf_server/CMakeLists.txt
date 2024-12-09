include("${CMAKE_CURRENT_SOURCE_DIR}/vendor/zlib.cmake")
include("${CMAKE_CURRENT_SOURCE_DIR}/vendor/drogon.cmake")
include("${CMAKE_CURRENT_SOURCE_DIR}/vendor/protobuf.cmake")
include("${CMAKE_CURRENT_SOURCE_DIR}/vendor/grpc.cmake")

file(GLOB_RECURSE ETCDF_PROTO_SOURCES src/*.proto)
add_library(etcdfproto ${ETCDF_PROTO_SOURCES})
target_link_libraries(
    etcdfproto PUBLIC protobuf::libprotobuf gRPC::grpc gRPC::grpc++
)
target_include_directories(
    etcdfproto PUBLIC ${CMAKE_CURRENT_BINARY_DIR}
)
set(grpc_cpp_plugin_location $<TARGET_FILE:gRPC::grpc_cpp_plugin>)
protobuf_generate(TARGET etcdfproto LANGUAGE cpp)
protobuf_generate(
    TARGET etcdfproto
    LANGUAGE grpc
    GENERATE_EXTENSIONS .grpc.pb.h .grpc.pb.cc
    PLUGIN "protoc-gen-grpc=${grpc_cpp_plugin_location}"
)
get_target_property(CHECK etcdfproto INTERFACE_INCLUDE_DIRECTORIES)
cmake_print_variables(CHECK)
file(GLOB_RECURSE ETCDF_SERVER_HEADERS src/*.hpp src/*.h)
file(GLOB_RECURSE ETCDF_SERVER_SOURCES src/*.cpp src/*.c)
filter_items(ETCDF_SERVER_HEADERS ".*__tests__.*")
filter_items(ETCDF_SERVER_SOURCES ".*__tests__.*")
add_library(
    etcdfserver
    ${ETCDF_SERVER_SOURCES}
)
set_property(TARGET etcdfserver PROPERTY CXX_STANDARD 23)
target_link_libraries(
    etcdfserver
    PUBLIC ipaddress::ipaddress
    PRIVATE etcdfproto drogon jsoncpp_static
)
target_include_directories(
    etcdfserver
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src/
)
