#pragma once

#include "Scene.hpp"

class Engine;

class InGameScene : public Scene
{
public:
	InGameScene(Engine& engine);
	~InGameScene();

	void Start() final;
	void Update(const float& deltaTime) final;
	void Render(sf::RenderTarget* renderTarget) final;
};