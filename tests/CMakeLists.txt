cmake_minimum_required(VERSION 3.10)

project(tests)

add_subdirectory("../external/googletest" "external/googletest")

add_subdirectory(unit)
add_subdirectory(integration)