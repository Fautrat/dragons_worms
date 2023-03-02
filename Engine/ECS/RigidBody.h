#pragma once

#include "Entity.h"
#include <sfml/Graphics.hpp>
#include "Component.h"
#include <iostream>
#include "../Utils/Vectormath.h"
#include <vector>
#include "SpriteRenderer.h"
constexpr float PI = 3.14f;


class Rigidbody : public Component
{
public:

	Rigidbody() = default;
	Rigidbody(float density, bool isStatic, float restitution, float gravity_scale) : restitution(restitution), density(density), isStatic(isStatic), m_gravity_scale(gravity_scale) {};
	~Rigidbody() = default;

	bool init() override final;

	void update(const float& deltaTime) override final {
		if(!isStatic)
		{
			if (isInputMovement)
			{
				m_velocity.x = m_velocity.x * deltaTime;
				m_velocity.y = m_velocity.y + (m_gravity_scale * gravity * deltaTime);
			}
			else
			{
				m_velocity += sf::Vector2f(0.f, m_gravity_scale * gravity * deltaTime);
			}
		}
		
		translate(m_velocity, m_rotation);
	}

	void setGravity(float newGravity)
	{
		gravity = newGravity;
	}
	void setMovementSpeed(const float speed) { m_speed = speed; }
	void moveHorizontal(int direction) 
	{
		isInputMovement = true;
		m_velocity.x =+ m_speed * direction;
	}
	void setVelocityY(const float newVelocityY) { m_velocity.y = newVelocityY; }
	void setVelocityX(const float newVelocityX) { m_velocity.x = newVelocityX; }

	void moveTo(sf::Vector2f newPosition)
	{
		entity->getComponent<Transform>()->moveTo(newPosition);
		transformUpdateRequired = true;
		onCollision = false;
	}

	void Rotate(float amount)
	{
		entity->getComponent<Transform>()->Rotate(amount);
		transformUpdateRequired = true;
	}

	void translate(sf::Vector2f v,float rotation) {
		transformUpdateRequired = true;
		entity->getComponent<Transform>()->translate(v, rotation);
	}

	void setVelocity(sf::Vector2f value)
	{
		m_velocity = value;
	}

	void Jump()
	{
		if (m_velocity.y == 0)
			m_velocity.y = -m_jumpForce;
	}

	void landing() { isOnGround = true; }
	sf::Vector2f getVelocity() { return m_velocity; };
	void InitValues(sf::Vector2f position,float mass,float restitution,float area);
	float getInvMass() {return invMass;}
private:
	//NEEDED
	float gravity = 9.81f;
	float invMass = 0;
	float m_gravity_scale = 1.0f;
	float m_speed = 200;
	float m_jumpForce = 8.0f;
	float mass = 0;
	float radius = 0;
	float m_rotation = 0;
	sf::Vector2f m_velocity = sf::Vector2f();
	sf::Vector2f position;
	bool isOnGround = true;
	bool isInputMovement = false;

public:
	bool onCollision = false;
	bool transformUpdateRequired;
	float density;
	bool isStatic = true;
	sf::Vector2f normal = sf::Vector2f();
	float restitution;
	float getMass() { return mass; };
	float getRestitution() { return restitution;};
	bool getIsStatic() { return isStatic; };
	float getRadius() { return radius; };
};