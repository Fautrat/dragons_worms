cmake_minimum_required(VERSION 3.20)
set(CMAKE_TOOLCHAIN_FILE ${CMAKE_SOURCE_DIR}/vcpkg/scripts/buildsystems/vcpkg.cmake)

project(dragons_worms)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(Engine)
add_subdirectory(Game)