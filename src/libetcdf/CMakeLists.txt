file(GLOB_RECURSE ETCDF_LIB_HEADERS src/*.hpp src/*.h)
file(GLOB_RECURSE ETCDF_LIB_SOURCES src/*.cpp src/*.c)

filter_items(ETCDF_LIB_HEADERS ".*__tests__.*")
filter_items(ETCDF_LIB_SOURCES ".*__tests__.*")
add_library(
    libetcdf
    ${ETCDF_LIB_SOURCES}
)
set_property(TARGET libetcdf PROPERTY CXX_STANDARD 23)
target_include_directories(
    libetcdf
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src/
)
