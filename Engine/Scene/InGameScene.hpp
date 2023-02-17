#pragma once

#include "Scene.hpp"
#include "../../Game/dragons.hpp"
#include "../ECS/EntityManager.h"
#include "../ECS/Entity.h"
#include "../ECS/Sprite.h"
#include "../ECS/ECS.h"

class Engine;

class InGameScene : public Scene
{

private:
	sf::Texture backgroundTexture;
	sf::Sprite backgroundSprite;
	Dragon* player;
#pragma region ECS
	EntityManager* m_manager;

#pragma endregion ECS

public:
	InGameScene(Engine& engine);
	~InGameScene();

	void Start() final;
	void Update(const float& deltaTime) final;
	void Render(sf::RenderTarget* renderTarget) final;

};