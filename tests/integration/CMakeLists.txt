cmake_minimum_required(VERSION 3.10)

project(integration)

file(GLOB_RECURSE UNIT_SRC "*.cpp")

add_executable(integration "${UNIT_SRC}")

target_link_libraries(integration gmock_main converter_arch)

target_include_directories(integration
    PRIVATE "$<TARGET_PROPERTY:converter_arch,INCLUDE_DIRECTORIES>"
    )

target_link_directories(integration
    PRIVATE "$<TARGET_PROPERTY:converter_arch,LIBRARY_OUTPUT_DIRECTORY>"
    )