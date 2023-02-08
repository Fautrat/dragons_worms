set(ENGINE_HEADERS
        Engine.h "Scene/Scene.hpp" "Scene/MainMenuScene.hpp" "Scene/InGameScene.hpp" "UI/UI.hpp")

set(ENGINE_SOURCES
        Engine.cpp "Scene/Scene.cpp" "Scene/MainMenuScene.cpp" "Scene/InGameScene.cpp" "UI/UI.cpp")

find_package(SFML COMPONENTS system window graphics audio CONFIG REQUIRED)

add_library(Engine
        STATIC ${ENGINE_HEADERS} ${ENGINE_SOURCES})

target_link_libraries(Engine
        PUBLIC sfml-system sfml-network sfml-graphics sfml-window sfml-audio)