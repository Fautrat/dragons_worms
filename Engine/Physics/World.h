#pragma once
#include <sfml/Graphics.hpp>
#include <iostream>
#include "Collision.h"
#include "../Utils/Vectormath.h"

class World
{
public:
	World();
	~World();

	bool Collide(Entity& firstEntity, Entity& secondEntity);
	void updatePhysics(std::vector<Entity*>& entities);
	void resolveCollision(Entity& firstEntity, Entity& secondEntity);
private:
	 
	 Collision* collision;
	 VectorMath<float> vecMath;
	 sf::Vector2f normal;
	 float depth;

};