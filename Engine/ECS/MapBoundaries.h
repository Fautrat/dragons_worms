#pragma once
#include "Entity.h"
#include "SpriteRenderer.h"
#include "Collider2D.h"

struct MapBoundaries : public Entity
{
	MapBoundaries(float x, float y, float scaleX, float scaleY)
	{
		getComponent<Transform>()->setTransform(x + 40.f, y + 45.f, 0, 0, scaleX, scaleY);
		addComponent<SpriteRenderer>(std::string("Dirt"));
		getComponent<SpriteRenderer>()->getSprite()->setColor(sf::Color::Transparent);
		addComponent<Rigidbody>(1, true, 0.5f, 1.f);
		addComponent<Collider2D>(BOX);
	}

	~MapBoundaries() = default;
};