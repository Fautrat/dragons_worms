#pragma once
#include "Entity.h"
#include "SpriteRenderer.h"
#include "Collider2D.h"

struct Ground : public Entity
{
	Ground(float x, float y, std::string tile)
	{
		Entity();
		getComponent<Transform>().setTransform(x, y, 0, 0, 1, 1);
		addComponent<SpriteRenderer>("Ground");
		getComponent<SpriteRenderer>().getSprite()->setOrigin(0, 0);
		if (tile == "GRASS")
		{
			getComponent<SpriteRenderer>().getSprite()->setTextureRect(sf::IntRect(0, 130, 96, 10));
			getComponent<SpriteRenderer>().getSprite()->setScale(sf::Vector2f(1.375f, 9.f));
		}
			
		else if (tile == "DIRT")
		{
			getComponent<SpriteRenderer>().getSprite()->setTextureRect(sf::IntRect(36, 30, 33, 33));
		}
		else if (tile == "/")
		{
			getComponent<SpriteRenderer>().getSprite()->setTextureRect(sf::IntRect(192, 128, 33, 33));
		}
		else if (tile == std::string("\\"))
		{
			getComponent<SpriteRenderer>().getSprite()->setTextureRect(sf::IntRect(225, 128, 33, 33));
		}
		getComponent<SpriteRenderer>().getSprite()->setScale(sf::Vector2f(4.125f, 3.375f));
		//addComponent<Rigidbody>(1, true, 0.7, 0);
		addComponent<Collider2D>(BOX);
	}

	~Ground() = default;
};