cmake_minimum_required(VERSION 3.10)

project(task-runner)

file(GLOB SRC "*.cpp")

add_library(task-runner "${SRC}")

target_include_directories(task-runner
    PRIVATE "."
    PRIVATE "${COMMON_INCLUDE_DIR}"
    )
