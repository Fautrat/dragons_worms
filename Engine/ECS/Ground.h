#pragma once
#include "Entity.h"
#include "SpriteRenderer.h"
#include "Collider2D.h"

struct Ground : public Entity
{
	Ground(float x, float y, float scaleX, float scaleY, std::string tile)
	{
		getComponent<Transform>()->setTransform(x + 40.f, y + 45.f, 0, 0, scaleX, scaleY);
		addComponent<SpriteRenderer>(tile);

		addComponent<Rigidbody>(1, true, 0.5f, 1.f);
		if(tile == std::string("Left_Diag"))
			addComponent<Collider2D>(TRIANGLE, UPLEFT);
		else if(tile == std::string("Right_Diag"))
			addComponent<Collider2D>(TRIANGLE, UPRIGHT);
		else 
			addComponent<Collider2D>(BOX);
	}

	~Ground() = default;
};