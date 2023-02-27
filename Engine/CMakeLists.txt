set(ENGINE_HEADERS
        Engine.h "Scene/Scene.hpp" "Scene/MainMenuScene.hpp" "Scene/InGameScene.hpp" "UI/UI.hpp" "ECS/ECS.h"
        "ECS/Component.h" "ECS/Entity.h"  "ECS/Transform.h" "ECS/EntityManager.h" "ECS/SpriteRenderer.h"
        "AssetManager/AssetManager.h"  "ECS/RigidBody.h" "Physics/Collision.h" "ECS/PolygonCollider2D.h" "ECS/Input.h" "ECS/SphereCollider2D.h"  "Utils/Vectormath.h" "Physics/World.h"  "ECS/Collider2D.h" "Physics/ECollisionType.h")

set(ENGINE_SOURCES
        Engine.cpp "Scene/Scene.cpp" "Scene/MainMenuScene.cpp" "Scene/InGameScene.cpp" "UI/UI.cpp"
        "ECS/EntityManager.cpp" "AssetManager/AssetManager.cpp" "Physics/Collision.cpp" "ECS/RigidBody.cpp" "ECS/PolygonCollider2D.cpp" "ECS/SphereCollider2D.cpp" "Physics/World.cpp" "ECS/Collider2D.cpp")

find_package(SFML COMPONENTS system window graphics audio CONFIG REQUIRED)

add_library(Engine
        STATIC ${ENGINE_HEADERS} ${ENGINE_SOURCES})

target_link_libraries(Engine
        PUBLIC sfml-system sfml-network sfml-graphics sfml-window sfml-audio)