#pragma once

#include "Scene.hpp"
#include "../../Game/dragons.hpp"
#include "../ECS/EntityManager.h"
#include "../ECS/Entity.h"
#include "../ECS/SpriteRenderer.h"
#include "../ECS/ECS.h"
#include "../ECS/RigidBody.h"
#include "../ECS/PolygonCollider2D.h"
#include "../ECS/Collider2D.h"
#include "../ECS/Input.h"
#include "../Physics/World.h"
#include "../ECS/Ground.h"

#include <memory>
class Engine;

class InGameScene : public Scene
{

private:
	sf::Texture backgroundTexture;
	sf::Sprite backgroundSprite;
	Dragon* player;
	EntityManager* m_manager;

	Entity dragon, box1, box2, circle, circle2, circle3, Triangle, ground;

	std::vector<Ground*> tileset;

public:
	InGameScene(Engine& engine);
	~InGameScene();

	void readMap();
	void Start() final;
	void Update(const float& deltaTime) final;
	void Render(sf::RenderTarget* renderTarget) final;

	std::unique_ptr<World> worldptr = std::make_unique<World>();
	
};