cmake_minimum_required(VERSION 3.17)
project(doctest)

set(CMAKE_CXX_STANDARD 17)

add_executable(tests tests_main.cpp)

add_library(doctest STATIC doctest.cpp)
find_package(SFML 2.5 REQUIRED graphics network audio window system)
target_include_directories(doctest PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/>)
set_target_properties(doctest PROPERTIES CXX_STANDARD 11 CXX_STANDARD_REQUIRED ON)

target_link_libraries(tests sfml-graphics)

