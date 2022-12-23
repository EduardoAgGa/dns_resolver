cmake_minimum_required(VERSION 3.16.0)

project(
    dns-resolver-library
    LANGUAGES C
    VERSION 0.1.0
)

add_library(
    dns_resolver_common
    INTERFACE
)
target_include_directories(
    dns_resolver_common
    INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}/common
)

add_subdirectory(impl)

add_library(
    dns_resolver_headers
    INTERFACE
)
target_include_directories(
    dns_resolver_headers
    INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}
)

add_library(
    dns_resolver_obj
    OBJECT
    ${CMAKE_CURRENT_SOURCE_DIR}/dns_resolver.c
)
target_link_libraries(
    dns_resolver_obj
    PUBLIC
    dns_resolver_common
    dns_resolver_headers
    dns_resolver_impl_headers
)

add_library(
    dns_resolver_st
    STATIC
)
target_link_libraries(
    dns_resolver_st
    PUBLIC
    dns_resolver_common
    dns_resolver_headers
    $<TARGET_OBJECTS:dns_resolver_obj>
    dns_resolver_impl_obj
)
