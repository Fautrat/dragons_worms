set(GAME_HEADERS
        Game.hpp
        Dragons.hpp
        InputHandler.hpp
)

set(GAME_SOURCES
        Game.cpp
        Dragons.cpp
        InputHandler.cpp
        main.cpp)

add_executable(Game ${GAME_HEADERS} ${GAME_SOURCES})

include_directories(${CMAKE_SOURCE_DIR}/Engine)

target_link_libraries(Game Engine)

install(TARGETS Game RUNTIME DESTINATION bin)
