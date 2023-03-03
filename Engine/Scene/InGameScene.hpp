#pragma once

#include "Scene.hpp"
#include "../ECS/Dragon.h"
#include "../ECS/WindHandler.h"
#include "../ECS/EntityManager.h"
#include "../ECS/Entity.h"
#include "../ECS/SpriteRenderer.h"
#include "../ECS/ECS.h"
#include "../ECS/RigidBody.h"
#include "../ECS/PolygonCollider2D.h"
#include "../ECS/Collider2D.h"
#include "../UI/UI.hpp"
#include "../ECS/PlayerInterface.h"
#include "../ECS/Ground.h"
#include "./Menu/MenuManager.hpp"
#include "../ECS/MapBoundaries.h"

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
	Entity windLeft, windRight;
	WindHandler windHandler;
	int random_number;

    MenuManager* menuManager;

    void PauseScene();
    void ResumeScene();
	void EndingScene(int);
    void MainMenu();

public:
	InGameScene(Engine& engine);
	~InGameScene();

	void readMap();
	void Start() final;
	void Update(const float& deltaTime) final;
	void Render(sf::RenderTarget* renderTarget) final;

	float timer = 60.f;
	void newTurn();
	WhosTurn currentPlayer = Player1;
	EntityManager* m_manager;

    EStateScene state = EStateScene::RunningScene;


};