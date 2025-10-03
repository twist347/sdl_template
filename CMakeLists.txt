cmake_minimum_required(VERSION 3.20)

set(T sdl_template)

project(${T})

set(SDL3_DIR ${CMAKE_CURRENT_SOURCE_DIR}/external/SDL3-3.2.24)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_subdirectory(${SDL3_DIR})

add_executable(${T} main.c)
target_link_libraries(${T} PRIVATE SDL3::SDL3 m)
target_compile_options(${T} PRIVATE -Wall -Wextra -pedantic)