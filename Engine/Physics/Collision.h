#pragma once
#include <sfml/Graphics.hpp>
#include "../ECS/BoxCollider2D.h"
#include "../ECS/SphereCollider2D.h"
#include "../ECS/TriangleCollider2D.h"

class Collision {
public:
	//AABB collision handle
	//bool BoxAndBox(const sf::Rect<int>& rectA, const sf::Rect<int>& rectB);
	bool BoxAndBox(const BoxCollider2D& colA, const BoxCollider2D& colB);

	bool SphereAndBox(const SphereCollider2D& colA, const BoxCollider2D& colB);

	bool TriangleAndSphere(const TriangleCollider2D& colA, const SphereCollider2D& colB);

	bool linePoint(float x1, float y1, float x2, float y2, float px, float py);

	bool pointCircle(float px, float py, float cx, float cy, float r);

	//More precisely its box on the lines of the triangle
	bool BoxAndTriangle(const BoxCollider2D& colA, const TriangleCollider2D& colB);

	bool LineAndLine(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4);

	float dist(float x1, float y1, float x2, float y2);

	// TODO : BoxAndLine / BoxAndCircle
};