cmake_minimum_required(VERSION 3.10)

project(tests)

add_subdirectory("../external/googletest" "external/googletest")

file(GLOB_RECURSE TEST_COMMON_SRC "common/*.cpp")
set(TEST_COMMON_INC "${CMAKE_CURRENT_SOURCE_DIR}")

add_subdirectory(unit)
add_subdirectory(integration)