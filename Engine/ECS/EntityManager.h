#pragma once

#include <vector>
#include <memory>
#include "SFML/Graphics.hpp"
#include "../Physics/World.h"
class Entity;

class EntityManager {
protected:
	EntityManager() = default;
	~EntityManager() = default;
	
public:
	
	static EntityManager* getInstance();
	static void killInstance();
	EntityManager(EntityManager& other) = delete;
	void operator=(const EntityManager&) = delete;

	void draw(sf::RenderTarget* renderwindow);
	void update(const float& deltaTime);

	void addEntity(Entity* entity);
	void eraseEntity(Entity* entity);

protected:
	std::vector<Entity*> entities;
	static EntityManager* m_instance;
	std::unique_ptr<World> worldPtr = std::make_unique<World>();
};