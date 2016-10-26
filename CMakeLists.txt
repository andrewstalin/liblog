cmake_minimum_required(VERSION 3.2)
set(CMAKE_CONFIGURATION_TYPES Debug Release CACHE TYPE INTERNAL FORCE)
project(liblog.project)

set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/3rdparty/cmake-modules)

add_subdirectory("${CMAKE_SOURCE_DIR}/liblog")
add_subdirectory("${CMAKE_SOURCE_DIR}/3rdparty/gtest")
add_subdirectory("${CMAKE_SOURCE_DIR}/tests")



