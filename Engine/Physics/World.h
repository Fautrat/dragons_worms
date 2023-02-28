#pragma once
#include <sfml/Graphics.hpp>
#include <iostream>
#include "Collision.h"
#include "../Utils/Vectormath.h"

class Entity;

class World
{
public:
	World();
	~World();

	float getMinBodySize() { return MinBodySize; };
	float getMaxBodySize() { return MaxBodySize; };
	float getMinDensity() { return MinDensity; };
	float getMaxDensity() { return MaxDensity; };


	void addEntityWithPhysics(Entity& entity);

	void removeEntityWithPhysics(Entity& entity);
	
	Entity& getEntityWithPhysics(int index)
	{
		if (index > 0 || index <= entities.size())
		{
			return *entities[index];
		}
	}


	bool Collide(Entity* firstEntity, Entity* secondEntity);
	void updatePhysics(const float& deltaTime);

	void resolveCollision(Entity* firstEntity, Entity* secondEntity);
private:
	 
	 Collision* collision;
	 std::vector<Entity*> entities;
	 float MinBodySize = 1.0f * 1.0f;
	 float MaxBodySize = 129.0f * 129.0f;
	 float MinDensity = 0.5f; //g/cm^3
	 float MaxDensity = 21.4f;
	 VectorMath<float> vecMath;
	 sf::Vector2f normal;
	 float depth;

};