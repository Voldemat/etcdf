include("${CMAKE_CURRENT_SOURCE_DIR}/vendor/cli11.cmake")

file(GLOB_RECURSE ETCDF_CLI_SOURCES src/*.cpp src/*.c)
add_executable(
    etcdf
    src/main.cpp
    ${ETCDF_CLI_SOURCES}
)
set_property(TARGET etcdf PROPERTY CXX_STANDARD 23)
target_link_libraries(etcdf
    PRIVATE CLI11::CLI11
    PRIVATE etcdfserver
)
target_include_directories(
    etcdf
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src/
    PRIVATE SYSTEM ${CLI11_INCLUDE_DIR}
)
