#pragma once

#include <sfml/Graphics.hpp>
#include <string>
#include "Entity.h"
#include "Component.h"

class SphereCollider2D : public Component {
public:
	SphereCollider2D(float radius, float spriteWidth, float spriteHeight) : m_radius(radius), m_spriteWidth(spriteWidth), m_spriteHeight(spriteHeight)
	{
		
	}

	SphereCollider2D(float radius, float spriteWidth, float spriteHeight, std::string tag)
		: 
		m_radius(radius), collisionTag(tag),
		m_spriteWidth(spriteWidth),
		m_spriteHeight(spriteHeight)
	{

	}

	~SphereCollider2D()
	{
		delete transform;
	}

	bool init() override final
	{
		if (transform = &entity->getComponent<Transform>())
		if (transform)
			return true;
		else
		{
			std::cout << "Problème d'initialisation component SphereCollider" << std::endl;
			return false;
		}	
	}

	void draw(sf::RenderTarget* renderWindow) override final
	{

	}

	void update() override final
	{
		circle_position.x = transform->position.x + (m_spriteWidth /2);
		circle_position.y = transform->position.y + (m_spriteHeight /2);

	}

	std::string getCollisionTag() const {
		return collisionTag;
	}

private:
	friend class Collision;
	float m_radius = 0;
	sf::Vector2i circle_position = sf::Vector2i();
	std::string collisionTag = "";
	Transform* transform = nullptr;
	float m_spriteWidth = 0.f;
	float m_spriteHeight = 0.f;

};