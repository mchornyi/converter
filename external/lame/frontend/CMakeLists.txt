cmake_minimum_required(VERSION 3.10)

project(lame_frontend_arch)

file(GLOB LAME_FRONTEND_SRC "*.c")
list(REMOVE_ITEM LAME_FRONTEND_SRC "${CMAKE_CURRENT_SOURCE_DIR}/gpkplotting.c")
list(REMOVE_ITEM LAME_FRONTEND_SRC "${CMAKE_CURRENT_SOURCE_DIR}/gtkanal.c")
list(REMOVE_ITEM LAME_FRONTEND_SRC "${CMAKE_CURRENT_SOURCE_DIR}/mp3x.c")

add_library(${PROJECT_NAME} STATIC "${LAME_FRONTEND_SRC}")

target_compile_definitions(${PROJECT_NAME}
    PRIVATE -DHAVE_STDINT_H
    PRIVATE -DHAVE_LIMITS_H
    PRIVATE -DSTDC_HEADERS    
    )

if(NOT ieee754_float32_t)
target_compile_definitions(${PROJECT_NAME}
    PRIVATE -Dieee754_float32_t=float
    )
endif()

target_include_directories(${PROJECT_NAME}
    PRIVATE "../include"
    PRIVATE "../libmp3lame"
    PRIVATE "../"
    )

if(WIN32)
    target_link_libraries(${PROJECT_NAME} wsock32 ws2_32)
endif()