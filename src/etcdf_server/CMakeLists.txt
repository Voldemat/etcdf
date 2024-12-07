include("${CMAKE_CURRENT_SOURCE_DIR}/vendor/drogon.cmake")
include("${CMAKE_CURRENT_SOURCE_DIR}/vendor/ipaddress.cmake")
file(GLOB_RECURSE ETCDF_SERVER_HEADERS src/*.hpp src/*.h)
file(GLOB_RECURSE ETCDF_SERVER_SOURCES src/*.cpp src/*.c)

filter_items(ETCDF_SERVER_HEADERS ".*__tests__.*")
filter_items(ETCDF_SERVER_SOURCES ".*__tests__.*")
add_library(
    etcdfserver
    ${ETCDF_SERVER_SOURCES}
)
target_link_libraries(etcdfserver PRIVATE drogon jsoncpp_static ipaddress::ipaddress)
target_include_directories(
    etcdfserver
    INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/src/
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src/
)
if (ETCDF_SERVER_BUILD_TESTS)
    #include("${CMAKE_CURRENT_SOURCE_DIR}/CMakeTestLists.txt")
endif()
