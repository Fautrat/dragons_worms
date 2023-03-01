#include "EntityManager.h"
#include "Entity.h"

EntityManager* EntityManager::m_instance = nullptr;

EntityManager* EntityManager::getInstance() {
	if (m_instance == nullptr)
	{
		m_instance = new EntityManager;
	}
	return m_instance;
}

void EntityManager::killInstance() {
	if (m_instance != nullptr)
	{
		delete m_instance;
		m_instance = nullptr;
	}
}

void EntityManager::draw(sf::RenderTarget* renderwindow){
	for (auto& entity : entities)
		entity->draw(renderwindow);
}

void EntityManager::update(const float& deltaTime){
	for (auto& entity : entities) 
		entity->update(deltaTime);
	worldPtr->updatePhysics(entities);
}

void EntityManager::refresh(){

}

void EntityManager::addEntity(Entity* entity){
	
	std::unique_ptr<Entity> uniquePtr{ entity };
	auto test = &uniquePtr;
	entities.emplace_back(std::move(uniquePtr));
}

void EntityManager::eraseEntity(Entity* player)
{
}

Entity* EntityManager::cloneEntity(Entity* player)
{
	return nullptr;
}
