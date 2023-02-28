#pragma once
#include <sfml/Graphics.hpp>
#include "../ECS/PolygonCollider2D.h"
#include "../ECS/SphereCollider2D.h"
#include "../ECS/Collider2D.h"
#include "../ECS/RigidBody.h"
#include "../Utils/Vectormath.h"
#include <math.h>
#include "../ECS/Entity.h"


class Collision {

private:
	sf::Vector2f normal;
	float depth;
	VectorMath<float> vecMath;

	std::pair<float, float> ProjectVertices(std::vector<sf::Vector2f> vertices, sf::Vector2f axis);
	std::pair<float, float> ProjectCircle(sf::Vector2f center, float radius, sf::Vector2f axis);
	int FindClosestPointOnPolygons(sf::Vector2f center, std::vector<sf::Vector2f> vertices);
	sf::Vector2f FindArithmeticMean(std::vector<sf::Vector2f> vertices);

public:

	bool detectCollision(Entity& objA, Entity& objB)
	{
		if (!objA.hasComponent<Collider2D>() || !objB.hasComponent<Collider2D>()) return false;
		normal = sf::Vector2f(0, 0);
		depth = 0;
		ColliderType colTypeA = objA.getComponent<Collider2D>().getColliderType();
		ColliderType colTypeB = objB.getComponent<Collider2D>().getColliderType();
		// Je sais c'est pas beau mais manque de temps pour faire mieux
		if (colTypeA == BOX)
		{
			if (colTypeB == BOX)
			{
				return IntersectPolygons(objA, objB);
			}

			if (colTypeB == TRIANGLE)
			{
				return IntersectPolygons(objA, objB);
			}

			if (colTypeB == SPHERE)
			{
				return IntersectCirclePolygon(objA, objB);
			}
		}

		if (colTypeA == SPHERE)
		{
			if (colTypeB == BOX)
			{
				return IntersectCirclePolygon(objA, objB);
			}
			if (colTypeB == TRIANGLE)
			{
				return IntersectCirclePolygon(objA, objB);
			}
			if (colTypeB == SPHERE)
			{
				return IntersectCircles(objA, objB);
			}
		}

		if (colTypeA == TRIANGLE)
		{
			if (colTypeB == BOX)
			{
				return IntersectPolygons(objA, objB);
			}
			if (colTypeB == TRIANGLE)
			{
				return IntersectPolygons(objA, objB);
			}
			if (colTypeB == SPHERE)
			{
				return IntersectCirclePolygon(objA, objB);
			}
		}

		return false;
	}

	sf::Vector2f getNormal() { return normal; };
	float getDepth() { return depth; };
	bool IntersectCirclePolygon(Entity& objA, Entity& objB);
	bool IntersectPolygons(Entity& objA, Entity& objB);
	bool IntersectCircles(Entity& objA, Entity& objB);
};
