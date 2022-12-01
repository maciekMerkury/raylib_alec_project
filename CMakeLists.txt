cmake_minimum_required(VERSION 3.22)
project(raylib_alec)
add_subdirectory(src)

add_custom_target(
    run
    COMMAND raylib_alec
    DEPENDS raylib_alec
    WORKING_DIRECTORY ${CMAKE_PROJECT_DIR}
)

