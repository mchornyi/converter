cmake_minimum_required(VERSION 3.10)

project(integration)

file(GLOB_RECURSE INTEGRATION_SRC "*.cpp")

add_executable(${PROJECT_NAME} "${INTEGRATION_SRC}" 
    "${CONVERTER_COMMON_SRC}"
    "${CONVERTER_SRC}"
    "${TEST_COMMON_SRC}"
    )

target_link_libraries(${PROJECT_NAME} 
    gtest_main 
    converter_arch
    lame
    lame_frontend_arch
    )

target_include_directories(${PROJECT_NAME}
    PRIVATE "$<TARGET_PROPERTY:converter_arch,INCLUDE_DIRECTORIES>"
    PRIVATE "$<TARGET_PROPERTY:lame,INCLUDE_DIRECTORIES>"
    PRIVATE "$<TARGET_PROPERTY:lame_frontend_arch,INCLUDE_DIRECTORIES>"
    PRIVATE "${TEST_COMMON_INC}"
    )

target_link_directories(${PROJECT_NAME}
    PRIVATE "$<TARGET_PROPERTY:converter_arch,LIBRARY_OUTPUT_DIRECTORY>"
    PRIVATE "$<TARGET_PROPERTY:lame,LIBRARY_OUTPUT_DIRECTORY>"
    PRIVATE "$<TARGET_PROPERTY:lame_frontend_arch,LIBRARY_OUTPUT_DIRECTORY>"
    )

add_custom_target(copy-resources ALL
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_CURRENT_SOURCE_DIR}/res
    ${CMAKE_CURRENT_BINARY_DIR}/res
    )
add_dependencies(copy-resources integration)

add_custom_command(
    TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory 
    ${CMAKE_CURRENT_SOURCE_DIR}/res
    ${CMAKE_CURRENT_BINARY_DIR}/res
    )