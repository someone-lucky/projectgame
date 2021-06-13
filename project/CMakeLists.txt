cmake_minimum_required(VERSION 3.17)
project(project)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXE_LINKER_FLAGS "-static -static-libgcc")
set(SFML_STATIC_LIBRARIES TRUE)

add_executable(project main.cpp map.h)
add_subdirectory(doctest)

set(SFML_DIR "C:\\Users\\66236\\Desktop\\HW + Prj\\AaP\\SFML-2.5.1\\lib\\cmake\\SFML")  #поменять на свой путь к SFML

target_link_libraries(project sfml-graphics)

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake_modules")
find_package(SFML 2.5 REQUIRED graphics network audio window system)

