cmake_minimum_required(VERSION 3.10)

project(converter)

set(Converter_VERSION_MAJOR 1)

set(Converter_VERSION_MINOR 0)

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_CXX_STANDARD_REQUIRED True)

option(BUILD_GTESTS "Build GTests" ON)

configure_file(ConverterConfig.h.in ConverterConfig.h)

set(CONFIG_FILE "${PROJECT_BINARY_DIR}/ConverterConfig.h")

set(COMMON_INCLUDE_DIR "${PROJECT_SOURCE_DIR}/inc/common")

add_subdirectory("src/task-runner")

add_executable(converter main.cpp)

target_compile_definitions(converter PRIVATE -DCONFIG_FILE="${CONFIG_FILE}")

target_link_libraries(converter task-runner)

target_include_directories(converter
    PRIVATE "${PROJECT_BINARY_DIR}"
    PRIVATE "$<TARGET_PROPERTY:task-runner,INCLUDE_DIRECTORIES>"
    )

target_link_directories(converter
    PRIVATE "$<TARGET_PROPERTY:task-runner,LIBRARY_OUTPUT_DIRECTORY>"
    )

if(${BUILD_GTESTS})
    add_subdirectory(tests)
endif()

install(TARGETS converter 
        RUNTIME
        DESTINATION "${PROJECT_BINARY_DIR}/bin"
       )