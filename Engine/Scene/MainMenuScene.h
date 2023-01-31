#pragma once

#include "Scene.hpp"

class Engine;

class MainMenuScene : public Scene
{
public:
	MainMenuScene(Engine& engine);
	~MainMenuScene();

	void Start() final;
	void Update(const float& deltaTime) final;
	void Render(sf::RenderTarget* renderTarget) final;
};
