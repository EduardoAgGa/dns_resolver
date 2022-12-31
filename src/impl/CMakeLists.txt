cmake_minimum_required(VERSION 3.16.0)

project(
    dns-resolver-impl-library
    LANGUAGES C
    VERSION 0.1.0
)

add_library(
    dns_resolver_impl_headers
    INTERFACE
)
target_include_directories(
    dns_resolver_impl_headers
    INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}
)

add_library(
    dns_resolver_impl_obj
    OBJECT
    ${CMAKE_CURRENT_SOURCE_DIR}/resolver_impl.c
)
target_link_libraries(
    dns_resolver_impl_obj
    PRIVATE
    dns_resolver_common
    dns_resolver_impl_headers
    PUBLIC
    c-ares
)
