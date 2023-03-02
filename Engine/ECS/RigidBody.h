#pragma once

#include "Entity.h"
#include <sfml/Graphics.hpp>
#include "Component.h"
#include <iostream>
#include "../Utils/Vectormath.h"
#include <vector>
#include "SpriteRenderer.h"

//constexpr float GRAVITY = 9.81f;
constexpr float PI = 3.14f;


class Rigidbody : public Component
{
public:

	Rigidbody() = default;
	Rigidbody(float density, bool isStatic, float restitution, float gravity_scale) : restitution(restitution), density(density), isStatic(isStatic), m_gravity_scale(gravity_scale) {};
	~Rigidbody() { delete transform; }

	bool init() override final;

	void update(const float& deltaTime) override final {
		if (isInputMovement) 
		{
			m_velocity.x = m_velocity.x * deltaTime;
			m_velocity.y = m_velocity.y + (m_gravity_scale * gravity.y * deltaTime);
		}
		else 
		{
			m_velocity += (m_gravity_scale * gravity * deltaTime);
			m_velocity += force * deltaTime;
			force = sf::Vector2f(0, 0);
		}
		
		translate(m_velocity, m_rotation);
	}

	void AddForce(sf::Vector2f amount)
	{
		force = amount;
	}
	void setGravity(sf::Vector2f gravity)
	{
		this->gravity = gravity;
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
		transform->moveTo(newPosition);
		transformUpdateRequired = true;
		onCollision = false;
	}

	void Rotate(float amount)
	{
		transform->Rotate(amount);
		transformUpdateRequired = true;
	}

	void translate(sf::Vector2f v,float rotation) {
		transformUpdateRequired = true;
		transform->translate(v, rotation);
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
	sf::Vector2f gravity = sf::Vector2f(0, 9.81f);
	float invMass = 0;
	sf::Vector2f acceleration;
	sf::Vector2f force;
	float m_gravity_scale = 1.0f;
	float m_speed = 200;
	float forceMagnitude = 25;
	float m_jumpForce = 8.0f;
	float mass = 0;
	float area = 0;
	float radius = 0;
	float width = 0;
	float height = 0;
	float m_rotation = 0;
	sf::Vector2f m_velocity = sf::Vector2f();
	sf::Vector2f position;
	bool isOnGround = true;
	bool isInputMovement = false;
	float tempGravityScale = 0.0f;
	Transform* transform = nullptr;

public:
	bool onCollision = false;
	bool transformUpdateRequired;
	float density;
	bool isStatic = true;
	float restitution;
	float getDensity() { return density; };
	float getMass() { return mass; };
	float getRestitution() { return restitution;};
	float getArea() { return area; };
	bool getIsStatic() { return isStatic; };
	float getRadius() { return radius; };
	float getWidth() { return width; };
	float getHeight() { return height; };
};