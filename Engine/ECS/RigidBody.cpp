#include "RigidBody.h"

bool Rigidbody::init()
{
	transform = &entity->getComponent<Transform>();
	if (nullptr != transform)
	{
		transformUpdateRequired = true;
		return true;
	}
	return false;
}
void Rigidbody::InitValues(sf::Vector2f position, float mass,float restitution, float area)
{
	this->force = sf::Vector2f(0, 0);
	this->position = position;
	this->m_velocity = sf::Vector2f(0, 0);
	this->mass = mass;
	this->restitution = restitution;
	this->area = area;

	if (!isStatic)
	{
		invMass = 1.0f / this->mass;
	}
	else
	{
		invMass = 0;
	}


}

