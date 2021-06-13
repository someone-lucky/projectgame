cmake_minimum_required(VERSION 3.17)
project(doctest)

set(CMAKE_CXX_STANDARD 20)

add_executable(tests tests_main.cpp)

add_library(doctest STATIC doctest.cpp)
target_include_directories(doctest PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/>)
set_target_properties(doctest PROPERTIES CXX_STANDARD 11 CXX_STANDARD_REQUIRED ON)