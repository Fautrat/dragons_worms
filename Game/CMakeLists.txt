set(GAME_HEADERS
        dragons.hpp
 "Game.h")

set(GAME_SOURCES
        main.cpp "Game.cpp")

add_executable(Game ${GAME_HEADERS} ${GAME_SOURCES})

include_directories(${CMAKE_SOURCE_DIR}/Engine)

target_link_libraries(Game Engine)

install(TARGETS Game RUNTIME DESTINATION bin)
