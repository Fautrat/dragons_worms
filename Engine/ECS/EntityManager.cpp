#include "EntityManager.h"

EntityManager* EntityManager::m_instance = nullptr;

EntityManager* EntityManager::getInstance() 
{
	if (m_instance == nullptr)
	{
		m_instance = new EntityManager();
	}
	return m_instance;
}

void EntityManager::killInstance() 
{
	if (m_instance != nullptr)
	{
		delete m_instance;
		m_instance = nullptr;
	}
}

void EntityManager::draw(sf::RenderTarget* renderwindow)
{
	for (auto& entity : entities)
		entity->draw(renderwindow);
}

void EntityManager::update(const float& deltaTime)
{
	for (auto& entity : entities) 
		entity->update(deltaTime);
	worldPtr->updatePhysics(entities);
}

void EntityManager::addEntity(Entity* entity)
{
	
	//std::unique_ptr<Entity> uniquePtr{ entity };
	entities.emplace_back(std::move(entity));
}

void EntityManager::eraseEntity(Entity* entity)
{
	if (const auto it = std::find(entities.begin(), entities.end(), entity); it != entities.end())
	{
		entities.erase(it);
		delete entity;
	}
}

