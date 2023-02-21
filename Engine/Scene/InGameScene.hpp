#pragma once

#include "Scene.hpp"
#include "../../Game/dragons.hpp"
#include "../ECS/EntityManager.h"
#include "../ECS/Entity.h"
#include "../ECS/SpriteRenderer.h"
#include "../ECS/ECS.h"
#include "../ECS/RigidBody.h"
#include "../ECS/BoxCollider2D.h"
#include "../Physics/Collision.h"
#include "../ECS/Input.h"


class Engine;

class InGameScene : public Scene
{

private:
	sf::Texture backgroundTexture;
	sf::Sprite backgroundSprite;
	Dragon* player;
	EntityManager* m_manager;
	Entity* dragon = new Entity();
	Entity* wall = new Entity();
	Entity* circle = new Entity();
	Entity* Triangle = new Entity();

	Collision* collision = new Collision();
public:
	InGameScene(Engine& engine);
	~InGameScene();

	void Start() final;
	void Update(const float& deltaTime) final;
	void Render(sf::RenderTarget* renderTarget) final;

};