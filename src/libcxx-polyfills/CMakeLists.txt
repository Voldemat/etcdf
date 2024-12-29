add_library(libcxx_polyfills INTERFACE)
set_property(TARGET libcxx_polyfills PROPERTY CXX_STANDARD 23)
target_include_directories(
    libcxx_polyfills
    INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/src/
)
