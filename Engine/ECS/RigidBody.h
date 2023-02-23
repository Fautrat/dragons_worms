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
	~Rigidbody()
	{
		delete transform;
		delete rigidbody;
	}

	Rigidbody(float gravity_scale) : m_gravity_scale(gravity_scale) {}

	bool init() override final {
		transform = &entity->getComponent<Transform>();
		rigidbody = &entity->getComponent<Rigidbody>();
		if (nullptr != transform && nullptr != rigidbody)
		{
			return true;
		}
		return false;
	}

	void update(const float& deltaTime) override final{
		m_velocity.x = m_velocity.x * 0.9f * deltaTime;
		m_velocity.y = m_velocity.y + (m_gravity_scale * GRAVITY * deltaTime) ;

		transform->translate(m_velocity);
	}

	void setMovementSpeed(const float speed) {
		m_speed = speed;
	}

	void moveHorizontal(int direction) {
		m_velocity.x = m_speed * direction;
	}

	void setVelocityY(const float newVelocityY)
	{
		m_velocity.y = newVelocityY;
	}

	void setVelocityX(const float newVelocityX)
	{
		m_velocity.x = newVelocityX;
	}

	void Jump()
	{
		if (!isOnGround)
			return;
		m_velocity.y = -m_jumpForce;
		isOnGround = false;
	}

	void landing()
	{
		isOnGround = true;
	}


private:
	float m_gravity_scale = 1.0f;
	sf::Vector2f m_velocity = sf::Vector2f();
	float m_speed = 300.0f;
	float m_jumpForce = 8.0f;
	Transform* transform = nullptr;
	bool isOnGround = false;


};