cmake_minimum_required(VERSION 3.16.0)

project(
    dns-resolver-tests
    LANGUAGES CXX C
    VERSION 0.1.0
)

add_library(
    doctest
    INTERFACE
)
target_include_directories(
    doctest
    INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}/doctest
)

add_subdirectory(fakes)

add_executable(
    dns_resolver_unittests
    ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/dns_resolver_test.cpp
)
target_link_libraries(
    dns_resolver_unittests
    PRIVATE
    dns_resolver_common
    dns_resolver_headers
    $<TARGET_OBJECTS:dns_resolver_obj>
    resolver_fakes_obj
    doctest
)

add_executable(
    fake_resolver_unittests
    ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/fake_resolver_test.cpp
)
target_link_libraries(
    fake_resolver_unittests
    PRIVATE
    dns_resolver_common
    resolver_fakes_obj
    doctest
)

add_executable(
    dns_resolver_integrationtests
    ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/dns_resolver_ares_test.cpp
)
target_link_libraries(
    dns_resolver_integrationtests
    PRIVATE
    dns_resolver_st
    doctest
)

include(cmake/doctest.cmake)
doctest_discover_tests(dns_resolver_unittests)
doctest_discover_tests(dns_resolver_integrationtests)
doctest_discover_tests(fake_resolver_unittests)
