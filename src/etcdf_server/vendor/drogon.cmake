include(FetchContent)
include("${CMAKE_CURRENT_LIST_DIR}/drogon-deps/jsoncpp.cmake")
set(BUILD_CTL OFF CACHE INTERNAL "")
set(BUILD_EXAMPLES OFF CACHE INTERNAL "")
set(BUILD_ORM OFF CACHE INTERNAL "")
set(COZ_PROFILING OFF CACHE INTERNAL "")
set(BUILD_SHARED_LIBS OFF CACHE INTERNAL "")
set(BUILD_DOC OFF CACHE INTERNAL "")
set(BUILD_YAML_CONFIG OFF CACHE INTERNAL "")
set(USE_STATIC_LIBS_ONLY ON CACHE INTERNAL "")
set(BUILD_TESTING OFF CACHE INTERNAL "")
FetchContent_Declare(
    drogon
    GIT_REPOSITORY https://github.com/drogonframework/drogon
    GIT_TAG v1.9.8
)
FetchContent_MakeAvailable(drogon)
