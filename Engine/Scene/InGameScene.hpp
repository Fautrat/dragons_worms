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
#include "../UI/UI.hpp"
#include "../ECS/LifeBar.h"
#include "../ECS/Ground.h"
#include "./Menu/MenuManager.hpp"

enum WhosTurn
{
	Player1,
	Player2,
};

class Engine;

class InGameScene : public Scene
{

private:
	sf::Texture backgroundTexture;
	sf::Sprite backgroundSprite;

	Dragon player1, player2;
	Dragon* players[2] = {&player1, &player2};

	UI* ui;
	Collision* collision;
	Entity box1, box2, circle, circle2, circle3, Triangle, ground;

	std::vector<Ground*> tileset;

    MenuManager* menuManager;

    void PauseScene();
    void ResumeScene();
    void MainMenu();

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
	EntityManager* m_manager;

    EStateScene state = EStateScene::RunningScene;


};