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
	Player1,
	Player2,
};

enum StateTurn
{
	Running,
	Processing,
};

class Engine;

class InGameScene : public Scene
{

private:
	sf::Texture backgroundTexture;
	sf::Sprite backgroundSprite;

	Dragon player1, player2;

	UI* ui;
	Collision* collision = new Collision();
	Entity box1, box2, circle, circle2, circle3, Triangle, ground;

	std::vector<Ground*> tileset;

public:
	InGameScene(Engine& engine);
	~InGameScene();

	sf::Font* font;

	void readMap();
	void Start() final;
	void Update(const float& deltaTime) final;
	void Render(sf::RenderTarget* renderTarget) final;

	float timer = 10.f;
	void newTurn();
	WhosTurn currentPlayer = Player1;
	StateTurn currentState = Running;

	std::unique_ptr<World> worldptr = std::make_unique<World>();
	EntityManager* m_manager;
};