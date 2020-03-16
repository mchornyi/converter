cmake_minimum_required(VERSION 3.10)

project(unit)

file(GLOB_RECURSE UNIT_SRC "*.cpp")

add_executable(unit "${UNIT_SRC}" 
    "${TEST_COMMON_SRC}" 
    "${CONVERTER_COMMON_SRC}"
    )

target_link_libraries(unit gmock_main converter_arch)

target_include_directories(unit
    PRIVATE "$<TARGET_PROPERTY:converter_arch,INCLUDE_DIRECTORIES>"
    PRIVATE "${TEST_COMMON_INC}"
    )

target_link_directories(converter
    PRIVATE "$<TARGET_PROPERTY:converter_arch,LIBRARY_OUTPUT_DIRECTORY>"
    )