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
add_subdirectory("external/lame/frontend")

file(GLOB_RECURSE SRC "src/*.cpp")

add_library(${PROJECT_NAME}_arch "${SRC}")

target_include_directories(${PROJECT_NAME}_arch
    PUBLIC "src"
    PUBLIC "inc"
    )

add_executable(${PROJECT_NAME} main.cpp)

target_compile_definitions(${PROJECT_NAME} PRIVATE -DCONFIG_FILE="${CONFIG_FILE}")

target_link_directories(${PROJECT_NAME}
    PRIVATE "$<TARGET_PROPERTY:lame,LIBRARY_OUTPUT_DIRECTORY>")

target_link_libraries(${PROJECT_NAME} ${PROJECT_NAME}_arch lame)

target_include_directories(${PROJECT_NAME}
    PRIVATE "${PROJECT_BINARY_DIR}"
    )

if(${BUILD_GTESTS})
    add_subdirectory(tests)
endif()

install(TARGETS ${PROJECT_NAME} 
        RUNTIME
        DESTINATION bin
       )