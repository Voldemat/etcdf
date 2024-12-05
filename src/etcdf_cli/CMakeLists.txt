include("${CMAKE_CURRENT_SOURCE_DIR}/vendor/cli11.cmake")
include("${CMAKE_CURRENT_SOURCE_DIR}/vendor/rapidjson.cmake")

file(GLOB_RECURSE ETCDF_CLI_SOURCES src/*.cpp src/*.c)
add_executable(
    etcdf
    src/main.cpp
    ${ETCDF_CLI_SOURCES}
)
add_dependencies(etcdf RapidJSON)
target_link_libraries(etcdf
    PRIVATE CLI11::CLI11
    PRIVATE libetcdf
    PRIVATE RapidJSON
)
target_include_directories(
    etcdf
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src/
    PRIVATE SYSTEM ${CLI11_INCLUDE_DIR}
    PRIVATE SYSTEM ${RAPIDJSON_INCLUDE_DIR}
)
