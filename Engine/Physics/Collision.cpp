#include "Collision.h"
#include <math.h>

//SPHERE THEN POLYGON
bool Collision::IntersectCirclePolygon(Entity& objA, Entity& objB)
{
	sf::Vector2f center = sf::Vector2f(0, 0);
	float radius = 0;
	std::vector<sf::Vector2f> vertices;
	sf::Vector2f polygonCenter = sf::Vector2f(0, 0);

	if (objA.hasComponent<SphereCollider2D>())
	{
		center = objA.getComponent<SphereCollider2D>()->circle_position;
		radius = objA.getComponent<SphereCollider2D>()->m_radius;
		vertices = objB.getComponent<PolygonCollider2D>()->transformedVertices;
		polygonCenter = objB.getComponent<Transform>()->position;
	}
	else
	{
		center = objB.getComponent<SphereCollider2D>()->circle_position;
		radius = objB.getComponent<SphereCollider2D>()->m_radius;
		vertices = objA.getComponent<PolygonCollider2D>()->transformedVertices;
		polygonCenter = objA.getComponent<Transform>()->position;
	}

	normal = sf::Vector2f(0, 0);
	depth = std::numeric_limits<float>::max();

	
	sf::Vector2f axis = sf::Vector2f(0, 0);
	float axisDepth = 0.0f;

	for (int i = 0; i < vertices.size(); i++)
	{
		sf::Vector2f va = vertices[i];
		sf::Vector2f vb = vertices[(i + 1) % vertices.size()];

		sf::Vector2f edge = vb - va;
		axis = sf::Vector2f(-edge.y, edge.x);
		axis = vecMath.Normalize(axis);

		std::pair<int, int> minmaxVertices = ProjectVertices(vertices, axis);
		std::pair<int, int> minmaxCircle = ProjectCircle(center, radius, axis);

		if (minmaxVertices.first >= minmaxCircle.second || minmaxCircle.first >= minmaxVertices.second)
		{
			return false;
		}

		axisDepth = std::min<float>(minmaxCircle.second - minmaxVertices.first, minmaxVertices.second - minmaxCircle.first);

		if (axisDepth < depth)
		{
			depth = axisDepth;
			normal = axis;
		}
	}

	int cpIndex = FindClosestPointOnPolygons(center, vertices);
	sf::Vector2f cp = vertices[cpIndex];

	axis = cp - center;
	axis = vecMath.Normalize(axis);

	std::pair<int, int> minmaxVertices = ProjectVertices(vertices, axis);
	std::pair<int, int> minmaxCircle = ProjectCircle(center, radius, axis);

	if (minmaxVertices.first >= minmaxCircle.second || minmaxCircle.first >= minmaxVertices.second)
	{
		return false;
	}

	axisDepth = std::min<float>(minmaxCircle.second - minmaxVertices.first, minmaxVertices.second - minmaxCircle.first);

	if (axisDepth < depth)
	{
		depth = axisDepth;
		normal = axis;
	}
	polygonCenter = FindArithmeticMean(vertices);

	sf::Vector2f direction = polygonCenter - center;

	if (vecMath.Dot(direction, normal) < 0.0f)
	{
		normal = -normal;
	}

	if (objB.hasComponent<SphereCollider2D>())
	{
		normal = -normal;
	}

	return true;

}

bool Collision::IntersectPolygons(Entity& objA, Entity& objB)
{
	normal = sf::Vector2f(0, 0);
	depth = std::numeric_limits<float>::max();

	std::vector<sf::Vector2f> verticesA = objA.getComponent<PolygonCollider2D>()->transformedVertices;
	std::vector<sf::Vector2f> verticesB = objB.getComponent<PolygonCollider2D>()->transformedVertices;

	for (int i = 0; i < verticesA.size(); i++)
	{
		sf::Vector2f va = verticesA[i];
		sf::Vector2f vb = verticesA[(i + 1) % verticesA.size()];

		sf::Vector2f edge = vb - va;
		sf::Vector2f axis = sf::Vector2f(-edge.y, edge.x);
		axis = vecMath.Normalize(axis);
		
		std::pair<float, float> minmaxA = ProjectVertices(verticesA, axis);
		std::pair<float, float> minmaxB = ProjectVertices(verticesB, axis);

		if (minmaxA.first >= minmaxB.second || minmaxB.first >= minmaxA.second)
		{
			return false;
		}

		float axisDepth = std::min<float>(minmaxB.second - minmaxA.first, minmaxA.second - minmaxB.first);

		if (axisDepth < depth)
		{
			depth = axisDepth;
			normal = axis;
		}
	}

	for (int i = 0; i < verticesB.size(); i++)
	{
		sf::Vector2f va = verticesB[i];
		sf::Vector2f vb = verticesB[(i + 1) % verticesB.size()];

		sf::Vector2f edge = vb - va;
		sf::Vector2f axis = sf::Vector2f(-edge.y, edge.x);
		axis = vecMath.Normalize(axis);

		std::pair<float, float> minmaxA = ProjectVertices(verticesA, axis);
		std::pair<float, float> minmaxB = ProjectVertices(verticesB, axis);
		
	
		if (minmaxA.first >= minmaxB.second || minmaxB.first >= minmaxA.second)
		{
			return false;
		}

		float axisDepth = std::min<float>(minmaxB.second - minmaxA.first, minmaxA.second - minmaxB.first);

		if (axisDepth < depth)
		{
			depth = axisDepth;
			normal = axis;
		}
	}
	sf::Vector2f centerA = FindArithmeticMean(verticesA);
	sf::Vector2f centerB = FindArithmeticMean(verticesB);

	sf::Vector2f direction = centerB - centerA;

	if (vecMath.Dot(direction, normal) < 0.0f)
	{
		normal = -normal;
	}

	
	return true;
}

sf::Vector2f Collision::FindArithmeticMean(std::vector<sf::Vector2f> vertices)
{
	float sumX = 0.0f;
	float sumY = 0.0f;
	
	for (int i = 0; i < vertices.size(); i++)
	{
		sf::Vector2f v = vertices[i];
		sumX += v.x;
		sumY += v.y;
	}

	return sf::Vector2f(sumX / (float)vertices.size(), sumY / (float)vertices.size());
}

std::pair<float,float> Collision::ProjectVertices(std::vector<sf::Vector2f> vertices, sf::Vector2f axis)
{
	float min = std::numeric_limits<float>::max();
	float max = std::numeric_limits<float>::min();

	for (int i = 0; i < vertices.size(); i++)
	{
		sf::Vector2f v = vertices[i];
		float proj = vecMath.Dot(v, axis);

		if (proj < min) { min = proj; }
		if (proj > max) { max = proj; }
	}
	return std::make_pair(min, max);
}

std::pair<float, float> Collision::ProjectCircle(sf::Vector2f center, float radius, sf::Vector2f axis)
{
	sf::Vector2f direction = vecMath.Normalize(axis);
	sf::Vector2f directionAndRadius = direction * radius;

	sf::Vector2f p1 = center + directionAndRadius;
	sf::Vector2f p2 = center - directionAndRadius;

	float min = vecMath.Dot(p1, axis);
	float max = vecMath.Dot(p2, axis);

	if (min > max)
	{
		//Swap min and max values
		float t = min;
		min = max;
		max = t;
	}

	return std::make_pair(min, max);
}

int Collision::FindClosestPointOnPolygons(sf::Vector2f center, std::vector<sf::Vector2f> vertices)
{
	int result = -1;
	float minDistance = std::numeric_limits<float>::max();
	for (int i = 0; i < vertices.size(); i++)
	{
		sf::Vector2f v = vertices[i];
		float distance = vecMath.Distance(v, center);

		if (distance < minDistance)
		{
			minDistance = distance;
			result = i;
		}
	}
	return result;

}

bool Collision::IntersectCircles(Entity& objA, Entity& objB)
{
	sf::Vector2f centerA = objA.getComponent<SphereCollider2D>()->circle_position;
	sf::Vector2f centerB = objB.getComponent<SphereCollider2D>()->circle_position;
	float radiusA = objA.getComponent<SphereCollider2D>()->m_radius;
	float radiusB = objB.getComponent<SphereCollider2D>()->m_radius;

	float distance = vecMath.Distance(centerA, centerB);
	float radii = radiusA + radiusB;

	if(distance >= radii) return false;


	normal = vecMath.Normalize(centerB - centerA);
	depth = radii - distance;

	return true;
}

bool Collision::detectCollision(Entity& objA, Entity& objB)
{
	if (!objA.hasComponent<Collider2D>() || !objB.hasComponent<Collider2D>()) return false;
	normal = sf::Vector2f(0, 0);
	depth = 0;
	ColliderType colTypeA = objA.getComponent<Collider2D>()->getColliderType();
	ColliderType colTypeB = objB.getComponent<Collider2D>()->getColliderType();
	// Je sais c'est pas beau mais manque de temps pour faire mieux
	if (colTypeA == BOX)
	{
		if (colTypeB == BOX || colTypeB == TRIANGLE)
		{
			return IntersectPolygons(objA, objB);
		}
		else if (colTypeB == SPHERE)
		{
			return IntersectCirclePolygon(objA, objB);
		}
	}

	else if (colTypeA == SPHERE)
	{
		if (colTypeB == BOX || colTypeB == TRIANGLE)
		{
			return IntersectCirclePolygon(objA, objB);
		}
		else if (colTypeB == SPHERE)
		{
			return IntersectCircles(objA, objB);
		}
	}

	else if (colTypeA == TRIANGLE)
	{
		if (colTypeB == BOX || colTypeB == TRIANGLE)
		{
			return IntersectPolygons(objA, objB);
		}
		else if (colTypeB == SPHERE)
		{
			return IntersectCirclePolygon(objA, objB);
		}
	}
	return false;
}