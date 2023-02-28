#pragma once
#include "Entity.h"
#include "SpriteRenderer.h"
#include "Collider2D.h"

struct Ground : public Entity
{
	Ground(float x, float y, std::string tile)
	{
		Entity();
		getComponent<Transform>().setTransform(x + 66.f, y + 54.f, 0, 0, 0.6f, 0.5f);
		addComponent<SpriteRenderer>(tile);
		//getComponent<SpriteRenderer>().getSprite()->setOrigin(0, 0);
			
		//getComponent<SpriteRenderer>().getSprite()->setScale(sf::Vector2f(3.3f, 2.7f));

		addComponent<Rigidbody>(1, true, 0.7, 0);
		if(tile == std::string("Left_Diag") || tile == std::string("Right_Diag"))
			addComponent<Collider2D>(TRIANGLE);
		else 
			addComponent<Collider2D>(BOX);
	}

	~Ground() = default;
};