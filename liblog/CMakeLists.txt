cmake_minimum_required(VERSION 3.2)
set(CMAKE_CONFIGURATION_TYPES Debug Release CACHE TYPE INTERNAL FORCE)
project(liblog)

include(GetProjectFiles)
include(SetCompilerOptions)

set(LIBLOG_FILES)
get_project_files(LIBLOG_FILES)

add_library(${PROJECT_NAME} STATIC ${LIBLOG_FILES})
set_compiler_options()

if(LIBLOG_USE_WINAPI)
  target_compile_definitions(${PROJECT_NAME} PRIVATE LIBLOG_USE_WINAPI)
endif()

set_property(TARGET ${PROJECT_NAME} APPEND PROPERTY INCLUDE_DIRECTORIES
  "${CMAKE_CURRENT_SOURCE_DIR}/include"
  "${CMAKE_CURRENT_SOURCE_DIR}/src"
)
