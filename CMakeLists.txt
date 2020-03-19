cmake_minimum_required(VERSION 3.10)

project(converter)

find_package (Threads)

set(Converter_VERSION_MAJOR 1)

set(Converter_VERSION_MINOR 0)

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_CXX_STANDARD_REQUIRED True)

option(BUILD_GTESTS "Build GTests" ON)

configure_file(ConverterConfig.h.in ConverterConfig.h)

set(CONFIG_FILE "${PROJECT_BINARY_DIR}/ConverterConfig.h")

set(COMMON_INCLUDE_DIR "${PROJECT_SOURCE_DIR}/inc/")

if(NOT WIN32)
    add_compile_options(-Wall)
endif()

add_subdirectory("external/lame")
add_subdirectory("external/lame/frontend")

file(GLOB_RECURSE CONVERTER_ARCH_SRC "src/*.cpp")
list(REMOVE_ITEM CONVERTER_ARCH_SRC "${CMAKE_CURRENT_SOURCE_DIR}/src/converter/ConverterLame.cpp")
list(REMOVE_ITEM CONVERTER_ARCH_SRC "${CMAKE_CURRENT_SOURCE_DIR}/src/converter/ConverterHelper.cpp")

set(CONVERTER_COMMON_SRC "${CMAKE_CURRENT_SOURCE_DIR}/src/converter/ConverterHelper.cpp" )
set(CONVERTER_SRC "${CMAKE_CURRENT_SOURCE_DIR}/src/converter/ConverterLame.cpp" 
    "${CMAKE_CURRENT_SOURCE_DIR}/src/ConverterApp.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/ConverterAppSimple.cpp"
    )

add_library(${PROJECT_NAME}_arch STATIC "${CONVERTER_ARCH_SRC}")

target_include_directories(${PROJECT_NAME}_arch
    PUBLIC "src"
    PUBLIC "inc"
    )

add_executable(${PROJECT_NAME} main.cpp 
    "${CONVERTER_SRC}"
    "${CONVERTER_COMMON_SRC}"
    )

target_compile_definitions(${PROJECT_NAME} PRIVATE -DCONFIG_FILE="${CONFIG_FILE}")

target_link_directories(${PROJECT_NAME}
    PRIVATE "$<TARGET_PROPERTY:lame,LIBRARY_OUTPUT_DIRECTORY>"
    PRIVATE "$<TARGET_PROPERTY:lame_frontend_arch,LIBRARY_OUTPUT_DIRECTORY>"
    )

target_link_libraries(${PROJECT_NAME} 
    ${PROJECT_NAME}_arch 
    lame
    lame_frontend_arch
    "${CMAKE_THREAD_LIBS_INIT}")

target_include_directories(${PROJECT_NAME}
    PRIVATE "${PROJECT_BINARY_DIR}"
    PRIVATE "$<TARGET_PROPERTY:lame_frontend_arch,INCLUDE_DIRECTORIES>"
    )

if(${BUILD_GTESTS})
    add_subdirectory(tests)
endif()

install(TARGETS ${PROJECT_NAME} 
        RUNTIME
        DESTINATION bin
       )