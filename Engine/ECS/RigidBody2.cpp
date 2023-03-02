#include "RigidBody.h"
#include "Collider2D.h"

bool Rigidbody::init()
{
	if (nullptr != &entity->getComponent<Transform>())
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

void Rigidbody::update(const float& deltaTime)
{
	//if (isInputMovement)
	//{
	//	m_velocity.x *= deltaTime;
	//	m_velocity.y += (m_gravity_scale * gravity * deltaTime);
	//}
	//else
	//{
	//	//m_velocity += (m_gravity_scale * gravity * deltaTime);
	//	m_velocity.x *= deltaTime;
	//	m_velocity.y += gravity * deltaTime;
	//	m_velocity += force * deltaTime;
	//	force = sf::Vector2f(0, 0);
	//}
	if (entity->getComponent<Collider2D>().getCollisionTag() == "Fireball")
		int cpt = 0;

	if (entity->getComponent<Collider2D>().getCollisionTag() == "Player")
		int cpt = 0;

	m_velocity.x = m_velocity.x * deltaTime;
	m_velocity.y = m_velocity.y + (m_gravity_scale * gravity * deltaTime);

	translate(m_velocity, m_rotation);
}

void Rigidbody::Jump()
{
	if (m_velocity.y == 0)
		m_velocity.y = -m_jumpForce;
}

void Rigidbody::setVelocity(sf::Vector2f value)
{
	m_velocity = value;
}

void Rigidbody::translate(sf::Vector2f v, float rotation) {
	transformUpdateRequired = true;
	entity->getComponent<Transform>().translate(v, rotation);
}

void Rigidbody::Rotate(float amount)
{
	entity->getComponent<Transform>().Rotate(amount);
	transformUpdateRequired = true;
}

void Rigidbody::moveTo(sf::Vector2f newPosition)
{
	entity->getComponent<Transform>().moveTo(newPosition);
	transformUpdateRequired = true;
	onCollision = false;
}

void Rigidbody::moveHorizontal(int direction)
{
	isInputMovement = true;
	m_velocity.x = +m_speed * direction;
}

void Rigidbody::setMovementSpeed(const float speed)
{
	m_speed = speed; 
}

void Rigidbody::setGravity(float newGravity)
{
	gravity = newGravity;
}
void Rigidbody::AddForce(sf::Vector2f amount)
{
	force = amount;
}


