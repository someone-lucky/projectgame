cmake_minimum_required(VERSION 3.17)
project(project)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXE_LINKER_FLAGS "-static -static-libgcc")
set(SFML_STATIC_LIBRARIES TRUE)

add_executable(project game.cpp map.h)
add_subdirectory(doctest)

add_custom_command(TARGET project POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        "${CMAKE_CURRENT_LIST_DIR}/Main.png" "$<TARGET_FILE_DIR:project>")
add_custom_command(TARGET project POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        "${CMAKE_CURRENT_LIST_DIR}/evil.png" "$<TARGET_FILE_DIR:project>")
add_custom_command(TARGET project POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        "${CMAKE_CURRENT_LIST_DIR}/Industrial.png" "$<TARGET_FILE_DIR:project>")
add_custom_command(TARGET project POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        "${CMAKE_CURRENT_LIST_DIR}/font.TTF" "$<TARGET_FILE_DIR:project>")
add_custom_command(TARGET project POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        "${CMAKE_CURRENT_LIST_DIR}/begin.TTF" "$<TARGET_FILE_DIR:project>")

target_link_libraries(project sfml-graphics)

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake_modules")
find_package(SFML 2.5 REQUIRED graphics network audio window system)

