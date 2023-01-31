set(ENGINE_HEADERS
        Engine.h "Scene/Scene.hpp" "Scene/InGameScene.h" "Scene/MainMenuScene.h")

set(ENGINE_SOURCES
        "Engine.cpp" "Scene/Scene.cpp" "Scene/InGameScene.cpp" "Scene/MainMenuScene.cpp" )

find_package(SFML COMPONENTS system window graphics CONFIG REQUIRED)

add_library(Engine
        STATIC ${ENGINE_HEADERS} ${ENGINE_SOURCES})

target_link_libraries(Engine
        PUBLIC sfml-system sfml-network sfml-graphics sfml-window)