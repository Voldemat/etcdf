file(GLOB_RECURSE ETCDF_UTILS_SOURCES src/*.cpp)
add_library(etcdf_utils ${ETCDF_UTILS_SOURCES})
set_property(TARGET etcdf_utils PROPERTY CXX_STANDARD 23)
target_include_directories(
    etcdf_utils
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src/
)
