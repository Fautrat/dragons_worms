#pragma once

#include "Scene.hpp"
#include "../ECS/Dragon.h"
#include "../ECS/EntityManager.h"
#include "../ECS/Entity.h"
#include "../ECS/SpriteRenderer.h"
#include "../ECS/ECS.h"
#include "../ECS/RigidBody.h"
#include "../ECS/BoxCollider2D.h"
#include "../Physics/Collision.h"
#include "../ECS/Input.h"
#include "../UI/UI.hpp"
#include "../ECS/LifeBar.h"

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

	Entity player1, wall, circle, Triangle;
	Dragon player3, player2;

	WhosTurn currentPlayer = Player1;

	UI* ui;
	Collision* collision = new Collision();
public:
	InGameScene(Engine& engine);
	~InGameScene();

	void Start() final;
	void Update(const float& deltaTime) final;
	void Render(sf::RenderTarget* renderTarget) final;
	int timer = 10;

	void newTurn();

};