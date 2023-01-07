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
target_sources(
    dns_resolver_headers
    INTERFACE
    FILE_SET dns_resolver_headers_set TYPE HEADERS FILES ${CMAKE_CURRENT_SOURCE_DIR}/dns_resolver.h
)

add_library(
    dns_resolver_obj
    OBJECT
    ${CMAKE_CURRENT_SOURCE_DIR}/dns_resolver.c
)
target_compile_options(
    dns_resolver_obj
    PRIVATE
    $<$<CONFIG:Debug>:-Wall>
    $<$<CONFIG:Release>:-Wall -Werror>
)
target_link_libraries(
    dns_resolver_obj
    PRIVATE
    dns_resolver_common
    dns_resolver_headers
    dns_resolver_impl_headers
)

add_library(
    dns_resolver_st
    STATIC
    $<TARGET_OBJECTS:dns_resolver_obj>
    $<TARGET_OBJECTS:dns_resolver_impl_obj>
)
target_link_libraries(
    dns_resolver_st
    PUBLIC
    dns_resolver_headers
    c-ares
)

install(
    TARGETS dns_resolver_st dns_resolver_headers
    EXPORT dns_resolver
    ARCHIVE
    COMPONENT Development
    PUBLIC_HEADER
    COMPONENT Development
    FILE_SET dns_resolver_headers_set
    COMPONENT Development
)
install(
    EXPORT dns_resolver
    NAMESPACE eag::
    DESTINATION lib/cmake/dns_resolver
    COMPONENT Development
)
