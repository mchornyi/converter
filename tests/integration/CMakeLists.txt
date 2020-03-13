cmake_minimum_required(VERSION 3.10)

project(integration)

file(GLOB_RECURSE UNIT_SRC "*.cpp")

set(CONVERTER_LAME_SRC "../../src/ConverterLame.cpp")

add_executable(integration "${UNIT_SRC}" "${CONVERTER_LAME_SRC}")

target_link_libraries(integration 
    gmock_main 
    converter_arch
    lame
    lame_frontend_arch
    )

target_include_directories(integration
    PRIVATE "$<TARGET_PROPERTY:converter_arch,INCLUDE_DIRECTORIES>"
    PRIVATE "$<TARGET_PROPERTY:lame,INCLUDE_DIRECTORIES>"
    PRIVATE "$<TARGET_PROPERTY:lame_frontend_arch,INCLUDE_DIRECTORIES>"
    )

target_link_directories(integration
    PRIVATE "$<TARGET_PROPERTY:converter_arch,LIBRARY_OUTPUT_DIRECTORY>"
    PRIVATE "$<TARGET_PROPERTY:lame,LIBRARY_OUTPUT_DIRECTORY>"
    PRIVATE "$<TARGET_PROPERTY:lame_frontend_arch,LIBRARY_OUTPUT_DIRECTORY>"
    )
