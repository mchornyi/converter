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

#LAME_FRONTEND_ARCH
file(GLOB LAME_FRONTEND_SRC "external/lame/frontend/*.c")
list(REMOVE_ITEM LAME_FRONTEND_SRC "${CMAKE_CURRENT_SOURCE_DIR}/external/lame/frontend/gpkplotting.c")
list(REMOVE_ITEM LAME_FRONTEND_SRC "${CMAKE_CURRENT_SOURCE_DIR}/external/lame/frontend/gtkanal.c")
list(REMOVE_ITEM LAME_FRONTEND_SRC "${CMAKE_CURRENT_SOURCE_DIR}/external/lame/frontend/mp3x.c")

add_library(lame_frontend_arch "${LAME_FRONTEND_SRC}")
target_compile_definitions(lame_frontend_arch 
    PRIVATE -DHAVE_STDINT_H
    PRIVATE -DHAVE_LIMITS_H
    PRIVATE -DSTDC_HEADERS    
    )

if(NOT ieee754_float32_t)
target_compile_definitions(lame_frontend_arch
    PRIVATE -Dieee754_float32_t=float
    )
endif()

target_include_directories(lame_frontend_arch
    PRIVATE "external/lame/frontend"
    PRIVATE "external/lame/include"
    PRIVATE "external/lame/libmp3lame"
    PRIVATE "external/lame/"
    )
#LAME_FRONTEND_ARCH

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