#pragma once

#include <sfml/Graphics.hpp>
#include <string>
#include "Entity.h"
#include "Component.h"
#include "RigidBody.h"


class SphereCollider2D : public Component {
public:
	SphereCollider2D(){}

	SphereCollider2D(std::string tag){}

	~SphereCollider2D(){delete transform;}

	bool init() override final;

	void draw(sf::RenderTarget* renderWindow) override final{}

	void update(const float& deltaTime) override final
	{
		circle_position = transform->position;
	}

	std::string getCollisionTag() const {
		return collisionTag;
	}

private:
	friend class Collision;

	sf::Vector2f circle_position = sf::Vector2f();
	std::string collisionTag = "";
	Transform* transform = nullptr;
	Rigidbody* rb = nullptr;
	float m_spriteWidth, m_radius, m_spriteHeight = 0.f;


};