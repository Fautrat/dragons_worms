#pragma once

#include "EntityManager.h"
#include "Component.h"
#include "Transform.h"
#include "SpriteRenderer.h"

class Explosion : public Component, public sf::CircleShape
{
public:
	Explosion() : m_timer(0.f) {}
	~Explosion() = default;

	bool init() override final
	{
		if (nullptr != entity && entity->hasComponent<Transform>() && entity->hasComponent<SpriteRenderer>())
		{
			const auto& transform = entity->getComponent<Transform>();
			const auto& spriteRenderer = entity->getComponent<SpriteRenderer>();
			setPosition(sf::Vector2f{ transform->position.x, transform->position.y });
			setFillColor(sf::Color(225, 82, 51, 255));
			setRadius(spriteRenderer->getTexture()->getSize().x / 2.f);
			setOrigin(sf::Vector2f(spriteRenderer->getTexture()->getSize().x / 2, spriteRenderer->getTexture()->getSize().y / 2));
			return true;
		}
		return false;
	}

	void draw(sf::RenderTarget* renderwindow) override final
	{
		renderwindow->draw(*this);
	}

	void update(const float& deltaTime) override final
	{
		if (entity->hasComponent<Transform>())
		{
			/*m_timer += deltaTime;
			if (m_timer >= 1.f)
			{
				EntityManager::getInstance()->eraseEntity(entity);
				return;
			}*/
			const auto& transform = entity->getComponent<Transform>();
			setPosition(sf::Vector2f{ transform->position.x, transform->position.y });
		}
	}

private :
	float m_timer;
};