#pragma once

#include <vector>
#include <memory>
#include "SFML/Graphics.hpp"

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
	void refresh();

	void addEntity(Entity* player);
	void eraseEntity(Entity* player);
	Entity* cloneEntity(Entity* player);

private:
	std::vector<std::unique_ptr<Entity>> entities;
	static EntityManager* m_instance;
};