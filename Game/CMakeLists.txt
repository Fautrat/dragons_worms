set(GAME_HEADERS
        InputHandler.hpp
)

set(GAME_SOURCES
        InputHandler.cpp
        main.cpp)

add_executable(Game ${GAME_HEADERS} ${GAME_SOURCES})

include_directories(${CMAKE_SOURCE_DIR}/Engine)

target_link_libraries(Game Engine)

install(TARGETS Game RUNTIME DESTINATION bin)
