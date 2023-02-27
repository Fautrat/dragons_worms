#include "EntityManager.h"
#include "Entity.h"


void EntityManager::draw(sf::RenderTarget* renderwindow){
	for (auto& entity : entities)
		entity->draw(renderwindow);
}

void EntityManager::update(const float& deltaTime){
	for (auto& entity : entities) 
		entity->update(deltaTime);
}

void EntityManager::refresh(){

}

void EntityManager::addEntity(Entity* player){
	
	std::unique_ptr<Entity> uniquePtr{ player };
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
