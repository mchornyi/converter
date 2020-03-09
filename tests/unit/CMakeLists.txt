cmake_minimum_required(VERSION 3.10)

project(unit)

file(GLOB UNIT_SRC "*.cpp")

add_executable(unit "${UNIT_SRC}")

target_link_libraries(unit gtest_main task-runner)

target_include_directories(unit
    PRIVATE "$<TARGET_PROPERTY:task-runner,INCLUDE_DIRECTORIES>"
    )

target_link_directories(converter
    PRIVATE "$<TARGET_PROPERTY:task-runner,LIBRARY_OUTPUT_DIRECTORY>"
    )