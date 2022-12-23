cmake_minimum_required(VERSION 3.16.0)

cmake_policy(SET CMP0135 NEW)

project(
    dns-resolver
    LANGUAGES C CXX
    VERSION 0.1.0
)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include(CTest)
enable_testing()

include(FetchContent)
FetchContent_Declare(
    cares
    URL https://github.com/c-ares/c-ares/archive/refs/tags/cares-1_18_1.zip
)
set(CARES_STATIC OFF CACHE BOOL "" FORCE)
set(CARES_SHARED ON CACHE BOOL "" FORCE)
set(CARES_BUILD_TESTS OFF CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(cares)

add_subdirectory(src)
add_subdirectory(test)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
