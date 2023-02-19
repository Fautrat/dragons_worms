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
		m_velocity.x = m_force.x - m_drag.x;
		m_velocity.y = m_force.y + m_drag.y + m_gravity_scale * GRAVITY;
		transform->translate(m_velocity);
	}

	void setForce(const sf::Vector2f f) {m_force = f;}

private:
	//float mass 
	float m_gravity_scale = 1.0f;
	sf::Vector2f m_drag = sf::Vector2f();
	sf::Vector2f m_force = sf::Vector2f();
	sf::Vector2f m_velocity = sf::Vector2f();

	Transform* transform = nullptr;



};