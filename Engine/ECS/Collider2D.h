#pragma once

#include <string>
#include "Entity.h"
#include "../ECS/PolygonCollider2D.h"
#include "../ECS/SphereCollider2D.h"
#include "../Physics/ECollisionType.h"


class Collider2D : public Component
{
public:
	
	Collider2D(ColliderType col) : colliderType(col) {}
	Collider2D(ColliderType col, std::string tag) : collisionTag(tag), colliderType(col) {}

	bool init() {
		switch(colliderType)
		{
		case BOX:
			entity->addComponent<PolygonCollider2D>(colliderType);
			return true;
			break;
		case SPHERE:
			entity->addComponent<SphereCollider2D>();
			return true;
			break;
		case TRIANGLE:
			entity->addComponent<PolygonCollider2D>(colliderType);
			break;
		default:
			return false;
		}

	}

	ColliderType getColliderType()
	{
		return colliderType;
	}

	std::string getCollisionTag()
	{;
		return collisionTag;
	}


private:
	ColliderType colliderType;
	std::string collisionTag;
	// Only for triangle 

};