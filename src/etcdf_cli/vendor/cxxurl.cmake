include(FetchContent)
FetchContent_Declare(
    CxxUrl
    GIT_REPOSITORY https://github.com/chmike/CxxUrl
    GIT_TAG master
)
set(ENABLE_INSTALL OFF CACHE BOOL "")
FetchContent_MakeAvailable(CxxUrl)
