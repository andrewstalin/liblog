cmake_minimum_required(VERSION 3.2)
set(CMAKE_CONFIGURATION_TYPES Debug Release CACHE TYPE INTERNAL FORCE)
project(liblog.tests)

include(GetProjectFiles)
include(SetCompilerOptions)

set(LIBLOG_TESTS_FILES)
get_project_files(LIBLOG_TESTS_FILES)

file(GLOB TESTS_SAMPLES
  ${CMAKE_CURRENT_SOURCE_DIR}/samples/*
)
file(COPY ${TESTS_SAMPLES} DESTINATION samples)

add_executable(${PROJECT_NAME} ${LIBLOG_TESTS_FILES})
set_compiler_options()

set_property(TARGET ${PROJECT_NAME} APPEND PROPERTY INCLUDE_DIRECTORIES
    "${CMAKE_SOURCE_DIR}/liblog/include"
    "${CMAKE_SOURCE_DIR}/3rdparty/gtest/include"
    "${CMAKE_CURRENT_SOURCE_DIR}/include"
)

target_link_libraries(${PROJECT_NAME} gtest)
target_link_libraries(${PROJECT_NAME} liblog)