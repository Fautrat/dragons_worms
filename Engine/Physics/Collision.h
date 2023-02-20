#pragma once
#include <sfml/Graphics.hpp>
#include "../ECS/BoxCollider2D.h"

class Collision {
public:
	//AABB collision handle
	bool BoxAndBox(const sf::Rect<int>& rectA, const sf::Rect<int>& rectB);
	bool BoxAndBox(const BoxCollider2D& colA, const BoxCollider2D& colB);

	// TODO : BoxAndLine / BoxAndCircle
};