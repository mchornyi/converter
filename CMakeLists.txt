cmake_minimum_required(VERSION 3.10)

project(converter)

set(Converter_VERSION_MAJOR 1)

set(Converter_VERSION_MINOR 0)

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_CXX_STANDARD_REQUIRED True)

option(BUILD_GTESTS "Build GTests" ON)

configure_file(ConverterConfig.h.in ConverterConfig.h)

set(CONFIG_FILE "${PROJECT_BINARY_DIR}/ConverterConfig.h")

set(COMMON_INCLUDE_DIR "${PROJECT_SOURCE_DIR}/inc/")

add_compile_options(-Wall)

add_subdirectory("external/lame")

file(GLOB_RECURSE SRC "src/*.cpp")

add_library(converter_arch "${SRC}")

target_include_directories(converter_arch
    PUBLIC "src"
    PUBLIC "inc"
    )

add_executable(converter main.cpp)

target_compile_definitions(converter PRIVATE -DCONFIG_FILE="${CONFIG_FILE}")

target_link_libraries(converter converter_arch)

target_include_directories(converter
    PRIVATE "${PROJECT_BINARY_DIR}"
    )

if(${BUILD_GTESTS})
    add_subdirectory(tests)
endif()

install(TARGETS converter 
        RUNTIME
        DESTINATION bin
       )