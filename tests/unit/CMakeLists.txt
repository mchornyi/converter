cmake_minimum_required(VERSION 3.10)

project(unit)

file(GLOB_RECURSE UNIT_SRC "*.cpp")

add_executable(${PROJECT_NAME} "${UNIT_SRC}" 
    "${TEST_COMMON_SRC}" 
    "${CONVERTER_COMMON_SRC}"
    )

target_link_libraries(${PROJECT_NAME} gmock_main converter_arch)

target_include_directories(${PROJECT_NAME}
    PRIVATE "$<TARGET_PROPERTY:converter_arch,INCLUDE_DIRECTORIES>"
    PRIVATE "${TEST_COMMON_INC}"
    )

target_link_directories(converter
    PRIVATE "$<TARGET_PROPERTY:converter_arch,LIBRARY_OUTPUT_DIRECTORY>"
    )