#include "RigidBody.h"

bool Rigidbody::init()
{
	if (nullptr != entity->getComponent<Transform>())
	{
		transformUpdateRequired = true;
		return true;
	}
	return false;
}
void Rigidbody::InitValues(sf::Vector2f position, float mass,float restitution, float area)
{
	this->position = position;
	this->m_velocity = sf::Vector2f(0, 0);
	this->mass = mass;
	this->restitution = restitution;

	if (!isStatic)
	{
		invMass = 1.0f / this->mass;
	}
	else
	{
		invMass = 0;
	}
}

