file(GLOB_RECURSE ETCDF_LIB_HEADERS src/*.hpp src/*.h)
file(GLOB_RECURSE ETCDF_LIB_SOURCES src/*.cpp src/*.c)

filter_items(ETCDF_LIB_HEADERS ".*__tests__.*")
filter_items(ETCDF_LIB_SOURCES ".*__tests__.*")
add_library(
    libetcdf
    ${ETCDF_LIB_SOURCES}
)
target_include_directories(
    libetcdf
    INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/src/
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src/
)
get_target_property(LIBB_INCLUDES libetcdf INCLUDE_DIRECTORIES)
if (LIBETCDF_BUILD_TESTS)
    #include("${CMAKE_CURRENT_SOURCE_DIR}/CMakeTestLists.txt")
endif()
