cmake_minimum_required(VERSION 3.17)
project(project)

set(CMAKE_CXX_STANDARD 17)
option(SFML_STATIC_LIBRARIES "link to SFML staticly" TRUE)

add_executable(project game.cpp map.h)
add_subdirectory(doctest)

find_package(SFML 2.5 REQUIRED graphics network audio window system)

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
        "${CMAKE_CURRENT_LIST_DIR}/font.ttf" "$<TARGET_FILE_DIR:project>")
add_custom_command(TARGET project POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        "${CMAKE_CURRENT_LIST_DIR}/begin.ttf" "$<TARGET_FILE_DIR:project>")

target_link_libraries(project sfml-graphics)



