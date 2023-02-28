#pragma once

#include "Scene.hpp"
#include "../ECS/Dragon.h"
#include "../ECS/EntityManager.h"
#include "../ECS/Entity.h"
#include "../ECS/SpriteRenderer.h"
#include "../ECS/ECS.h"
#include "../ECS/RigidBody.h"
#include "../ECS/PolygonCollider2D.h"
#include "../ECS/Collider2D.h"
#include "../ECS/Input.h"
#include "../UI/UI.hpp"
#include "../ECS/LifeBar.h"

#include "../Physics/World.h"
#include "../ECS/Ground.h"

#include <memory>

enum WhosTurn
{
	Player1 = 0,
	Player2 = 1,
};

class Engine;

class InGameScene : public Scene
{

private:
	sf::Texture backgroundTexture;
	sf::Sprite backgroundSprite;
	EntityManager* m_manager;

	Dragon player

	WhosTurn currentPlayer = Player1;

	UI* ui;
	Collision* collision = new Collision();
	Entity box1, box2, circle, circle2, circle3, Triangle, ground;

	std::vector<Ground*> tileset;

public:
	InGameScene(Engine& engine);
	~InGameScene();

	void readMap();
	void Start() final;
	void Update(const float& deltaTime) final;
	void Render(sf::RenderTarget* renderTarget) final;
	int timer = 10;

	void newTurn();

	std::unique_ptr<World> worldptr = std::make_unique<World>();
	
};