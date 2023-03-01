#include "World.h"
#include "Collision.h"


World::World() {
	collision = new Collision();
}

World::~World()
{
	delete collision;
}



bool World::Collide(Entity& firstEntity, Entity& secondEntity)
{
	return collision->detectCollision(firstEntity, secondEntity);
}

void World::resolveCollision(Entity& firstEntity, Entity& secondEntity)
{
	Rigidbody& rbA = firstEntity.getComponent<Rigidbody>();
	Rigidbody& rbB = secondEntity.getComponent<Rigidbody>();
	rbA.onCollision = true;
	rbB.onCollision = true;
	sf::Vector2f relativeVelocity = rbB.getVelocity() - rbA.getVelocity();

	if (vecMath.Dot(relativeVelocity, normal) > 0.0f)
	{
		return;
	}

	float e = std::min(rbA.restitution, rbB.restitution);
	float j = -(1.0f + e) * vecMath.Dot(relativeVelocity, normal);
	j /= rbA.getInvMass() + rbB.getInvMass();

	sf::Vector2f impulse = j * normal;

	rbA.setVelocity(rbA.getVelocity() - impulse * rbA.getInvMass());
	rbB.setVelocity(rbB.getVelocity() + impulse * rbB.getInvMass());
}


void World::updatePhysics(std::vector<std::unique_ptr<Entity>>& entities)
{
	const auto copyEntities = entities;
	for (int i = 0; i < copyEntities.size() - 1; i++)
	{
		Entity& entityA = *entities[i];
		if (!entityA.hasComponent<Collider2D>()) continue;
		
		for (int j = i + 1; j < copyEntities.size(); j++)
		{
			Entity& entityB = *entities[j];
			if (!entityB.hasComponent<Collider2D>()) continue;

			if (entityA.getComponent<Rigidbody>().getIsStatic() && entityB.getComponent<Rigidbody>().getIsStatic()) continue;

			if (Collide(entityA, entityB))
			{
				if (entityA->getComponent<Collider2D>().getCollisionTag() == std::string("Fireball"))
				{
					if (entityB->getComponent<Collider2D>().getCollisionTag() == std::string("Player"))
					{
						continue;
					}
					removeEntityWithPhysics(*entityA);
					delete entityA;
					break;
				}
				else if (entityB->getComponent<Collider2D>().getCollisionTag() == std::string("Fireball"))
				{
					if (entityA->getComponent<Collider2D>().getCollisionTag() == std::string("Player"))
					{
						continue;
					}
					else
					{
						removeEntityWithPhysics(*entityA);
						continue;
					}
				}
				depth = collision->getDepth();
				normal = collision->getNormal();

				if (entityB.getComponent<Rigidbody>().getIsStatic())
				{
					entityA.getComponent<Rigidbody>().translate(-normal * depth, 0);
				}
				else if(entityA.getComponent<Rigidbody>().getIsStatic())
				{
					entityB.getComponent<Rigidbody>().translate(normal * depth, 0);
				}
				else
				{
					entityA.getComponent<Rigidbody>().translate(-normal * depth / 2.0f, 0);
					entityB.getComponent<Rigidbody>().translate(normal * depth / 2.0f, 0);
				}

				resolveCollision(entityA, entityB);
			}
		}
	}
}
