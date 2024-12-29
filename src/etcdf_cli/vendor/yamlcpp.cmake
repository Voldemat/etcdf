include(FetchContent)
set(YAML_CPP_BUILD_TOOLS OFF CACHE INTERNAL "")
set(YAML_BUILD_SHARED_LIBS OFF CACHE INTERNAL "")
FetchContent_Declare(
    yaml-cpp
    GIT_REPOSITORY https://github.com/jbeder/yaml-cpp.git
    GIT_TAG 0.8.0
)
FetchContent_MakeAvailable(yaml-cpp)
