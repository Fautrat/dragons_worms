#pragma once

#include "Entity.h"
#include <sfml/Graphics.hpp>
#include "Component.h"
#include <iostream>

constexpr float GRAVITY = 9.81f;

class Rigidbody : public Component
{
public:
	Rigidbody() = default;
	virtual ~Rigidbody() = default;

	Rigidbody(float gravity_scale) : m_gravity_scale(gravity_scale) {}

	bool init() override final {
		transform = &entity->getComponent<Transform>();
		return true;
	}

	void update() override final{
		applyJump();
		m_velocity.x =+ m_force.x - m_drag.x + directionX;
		m_velocity.y =+ m_force.y + m_drag.y + m_gravity_scale * GRAVITY + directionY;

		transform->translate(m_velocity);
	}

	void setForce(const sf::Vector2f f) {m_force = f;}
	void setMovementSpeed(const float speed) {
		m_speed = speed;
	}

	void moveHorizontal(int direction) {
		directionX = m_speed * direction;
	}

	void applyJump()
	{	
		timeSpentJump++;
		if (timeSpentJump >= 0.0f && jump == true)
		{
			directionY = -m_jumpForce;
			isOnGround = false;
		}

		if (timeSpentJump >= 20)
		{
			directionY = 0;
			jump = false;
			timeSpentJump = 0.0f;
		}
		
	}

	void isgrounded(bool state)
	{
		isOnGround = state;
	}
	void Jump()
	{
		jump = true;
	}




private:
	//float mass
	float timeSpentJump = 0.0f;
	float m_gravity_scale = 1.0f;
	sf::Vector2f m_drag = sf::Vector2f();
	sf::Vector2f m_force = sf::Vector2f();
	sf::Vector2f m_velocity = sf::Vector2f();
	float m_speed = 5.0f;
	float m_jumpForce = 25.0f;
	float directionX = 0.0f;
	float directionY = 0.0f;
	Transform* transform = nullptr;
	Rigidbody* rigidbody = nullptr;
	bool jump = false;
	bool isOnGround = false;



};