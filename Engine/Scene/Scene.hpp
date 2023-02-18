#pragma once

#include <SFML/Graphics.hpp>
#include "../Engine.h"
class Engine;


class Scene
{
public:
	Scene(Engine& engine);
	virtual ~Scene();

	virtual void Start() = 0;
	virtual void Update(const float& deltaTime) = 0;
	virtual void Render(sf::RenderTarget* renderTarget = nullptr) = 0;

	Engine& getParentEngine() const;

protected:
	Engine* engine;
	//std::vector<sf::Texture> _textures;
};