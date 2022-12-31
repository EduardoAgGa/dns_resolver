cmake_minimum_required(VERSION 3.16.0)

project(
    dns-resolver-fakes
    LANGUAGES C
    VERSION 0.1.0
)

add_library(
    resolver_fakes_headers
    INTERFACE
)
target_include_directories(
    resolver_fakes_headers
    INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}
)

add_library(
    resolver_fakes_obj
    OBJECT
    ${CMAKE_CURRENT_SOURCE_DIR}/fake_resolver_impl.c
)
target_link_libraries(
    resolver_fakes_obj
    PRIVATE
    dns_resolver_common
    dns_resolver_impl_headers
    PUBLIC
    resolver_fakes_headers
)
