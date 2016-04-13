cmake_minimum_required(VERSION 3.2)
set(CMAKE_CONFIGURATION_TYPES Debug Release CACHE TYPE INTERNAL FORCE)
project(liblog.tests)

list(APPEND LIBLOG_TESTS_FILES "")

file(GLOB_RECURSE PROJECT_FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/*.h
    ${CMAKE_CURRENT_SOURCE_DIR}/*.inl
    ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/*.c
)

foreach(PROJECT_FILE ${PROJECT_FILES})
    file(RELATIVE_PATH FILTER_PATH ${CMAKE_CURRENT_SOURCE_DIR} ${PROJECT_FILE})
    list(APPEND LIBLOG_TESTS_FILES ${PROJECT_FILE})
    string(REGEX REPLACE "(.*)(/[^/]*)$" "\\1" FILTER_PATH ${FILTER_PATH})
    string(REPLACE / \\ FILTER_PATH ${FILTER_PATH})
    source_group("${FILTER_PATH}" FILES ${PROJECT_FILE})
endforeach()

add_executable(${PROJECT_NAME} ${LIBLOG_TESTS_FILES})

if(MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE "/MT$<$<CONFIG:Debug>:d>" "-W3")
else()
    target_compile_options(${PROJECT_NAME} PRIVATE "-std=c++14" "-Wall" "-static")
endif()

list(APPEND LIBLOG_TESTS_INCLUDE_DIRS
    "${CMAKE_SOURCE_DIR}/liblog/include"
    "${CMAKE_SOURCE_DIR}/3rdparty/gtest/include"
    "${CMAKE_CURRENT_SOURCE_DIR}/include"
    "${CMAKE_SOURCE_DIR}/3rdparty/cppformat/"
)

set_property(TARGET ${PROJECT_NAME} APPEND PROPERTY INCLUDE_DIRECTORIES ${LIBLOG_TESTS_INCLUDE_DIRS})

target_link_libraries(${PROJECT_NAME} gtest)
target_link_libraries(${PROJECT_NAME} liblog)
target_link_libraries(${PROJECT_NAME} cppformat)