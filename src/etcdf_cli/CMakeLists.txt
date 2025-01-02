include("${CMAKE_CURRENT_SOURCE_DIR}/vendor/cli11.cmake")
include("${CMAKE_CURRENT_SOURCE_DIR}/vendor/yamlcpp.cmake")
include("${CMAKE_CURRENT_SOURCE_DIR}/vendor/cxxurl.cmake")

file(GLOB_RECURSE ETCDF_CLI_SOURCES src/*.cpp src/*.c)
set(
    CONFIG_CPP_PATH
    "${CMAKE_CURRENT_BINARY_DIR}/CMakeFiles/etcdf_cli_config.dir/config.cpp"
)
execute_process(
    COMMAND
    "${GIT_EXECUTABLE}" rev-parse --short HEAD
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    OUTPUT_VARIABLE ETCDF_GIT_SHA
    OUTPUT_STRIP_TRAILING_WHITESPACE
)
execute_process(
    COMMAND
    "${GIT_EXECUTABLE}" tag
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    OUTPUT_VARIABLE ETCDF_VERSION
    OUTPUT_STRIP_TRAILING_WHITESPACE
)
configure_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/cmake/config.cpp
    "${CONFIG_CPP_PATH}"
)
add_executable(
    etcdf
    src/main.cpp
    ${ETCDF_CLI_SOURCES}
    ${CONFIG_CPP_PATH}
)
set_property(TARGET etcdf PROPERTY CXX_STANDARD 23)
target_link_libraries(etcdf
    PRIVATE CLI11::CLI11
    PRIVATE etcdfserver
    PRIVATE yaml-cpp::yaml-cpp
    PRIVATE etcdf_utils
    PRIVATE chmike::CxxUrl
)
target_include_directories(
    etcdf
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src/
)
target_include_directories(
    etcdf
    SYSTEM
    PRIVATE ${CLI11_INCLUDE_DIR}
    PRIVATE $<TARGET_PROPERTY:yaml-cpp::yaml-cpp,INTERFACE_INCLUDE_DIRECTORIES>
)
