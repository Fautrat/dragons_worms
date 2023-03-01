#include "EntityManager.h"
#include "Entity.h"


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
