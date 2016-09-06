cmake_minimum_required(VERSION 3.1.0 FATAL_ERROR)
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

project(Stella)
add_subdirectory(src)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
  add_subdirectory(tests)
endif()
