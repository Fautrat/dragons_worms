cmake_minimum_required(VERSION 3.20)
set(CMAKE_TOOLCHAIN_FILE ${CMAKE_SOURCE_DIR}/vcpkg/scripts/buildsystems/vcpkg.cmake)

project(dragons_worms)


set(CMAKE_CXX_STANDARD 20)

add_subdirectory(Engine)
add_subdirectory(Game)

#file(COPY assets DESTINATION "${CMAKE_BINARY_DIR}")
#set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

#add_custom_command(
#	TARGET ${PROJECT_NAME}
#	POST_BUILD
#	COMMAND ${CMAKE_COMMAND} -E copy_directory
#	assets
#	$<TARGET_FILE_DIR:${PROJECT_NAME}>
#)