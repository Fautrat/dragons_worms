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

	float getMinBodySize() { return MinBodySize; };
	float getMaxBodySize() { return MaxBodySize; };
	float getMinDensity() { return MinDensity; };
	float getMaxDensity() { return MaxDensity; };

	bool Collide(Entity& firstEntity, Entity& secondEntity);
	void updatePhysics(std::vector<std::unique_ptr<Entity>>& entities);
	void resolveCollision(Entity& firstEntity, Entity& secondEntity);
private:
	 
	 Collision* collision;
	 float MinBodySize = 1.0f * 1.0f;
	 float MaxBodySize = 129.0f * 129.0f;
	 float MinDensity = 0.5f; //g/cm^3
	 float MaxDensity = 21.4f;
	 VectorMath<float> vecMath;
	 sf::Vector2f normal;
	 float depth;

};