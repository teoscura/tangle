cmake_minimum_required(VERSION 4.3)
project(tangle CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

option(RC_ENABLE_WARNINGS "Enable compiler warnings" ON)
add_compile_options(-Wall -Wextra -Wpedantic)

option(RELEASE "Release build" ON)
add_compile_options(-O3)

find_package(Boost REQUIRED)
find_package(GTest REQUIRED)

add_subdirectory(src/tangle)
add_subdirectory(src/test)