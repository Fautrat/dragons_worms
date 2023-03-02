#include "PolygonCollider2D.h"

bool PolygonCollider2D::init()
{
	if (entity->hasComponent<Transform>() && entity->hasComponent<Rigidbody>() && entity->hasComponent<SpriteRenderer>())
	{
		const auto& transform = entity->getComponent<Transform>();
		auto& rb = *entity->getComponent<Rigidbody>();
		auto& sr = *entity->getComponent<SpriteRenderer>();
		width = sr.getSprite()->getGlobalBounds().width;
		height = sr.getSprite()->getGlobalBounds().height;


		float area = width * height;
		
		float restitution = vecMath.Clamp(rb.restitution, 0.f, 1.f);
		float mass =(area * rb.density)/1000;

		rb.InitValues(transform->position, mass, restitution, area);
		switch (colType)
		{
		case BOX:
			CreateBoxVertices(width, height);
			break;
		case TRIANGLE:
			CreateTriangleVertices(width, height);
			break;
		default:
			break;
		}
		return true;
	}
	else
	{
		std::cout << "Problème d'initialisation component BoxCollider" << std::endl;
		std::cout << "You need to addComponent the Rigidbody before boxCollider" << std::endl;
		std::cout << "You need to addComponent the Transform before boxCollider" << std::endl;
		return false;
	}
}

void PolygonCollider2D::CreateBoxVertices(float width, float height)
{
	float left = -width / 2.0f;
	float right = width / 2.0f;
	float bottom = height / 2.0f;
	float top = -height / 2;


	vertices.push_back(sf::Vector2f(left, top));
	vertices.push_back(sf::Vector2f(right, top));
	vertices.push_back(sf::Vector2f(right, bottom));
	vertices.push_back(sf::Vector2f(left, bottom));
}

void PolygonCollider2D::CreateTriangleVertices(float width, float height)
{
	const auto& transform = entity->getComponent<Transform>();

	float left = -width / 2.0f;
	float right = width / 2.0f;
	float bottom = height / 2.0f;
	float top = -height / 2;
	float rotation = transform->rotation;

	/*if (rotation == 0)
	{
		vertices.push_back(sf::Vector2f(left, top));
		vertices.push_back(sf::Vector2f(0, 0));
		vertices.push_back(sf::Vector2f(right, bottom));
		vertices.push_back(sf::Vector2f(left, bottom));
	}
	if (rotation == 90)
	{
		vertices.push_back(sf::Vector2f(left, top));
		vertices.push_back(sf::Vector2f(right, top));
		vertices.push_back(sf::Vector2f(0, 0));
		vertices.push_back(sf::Vector2f(left, bottom));
	
	}
	if (rotation == 180)
	{
		vertices.push_back(sf::Vector2f(left, top));
		vertices.push_back(sf::Vector2f(right, top));
		vertices.push_back(sf::Vector2f(right, bottom));
		vertices.push_back(sf::Vector2f(0, 0));
	}
	if (rotation == 270 || rotation == -90)
	{
		vertices.push_back(sf::Vector2f(0, 0));
		vertices.push_back(sf::Vector2f(right, top));
		vertices.push_back(sf::Vector2f(right, bottom));
		vertices.push_back(sf::Vector2f(left, bottom));
	}*/
	
	switch (directionTriangle)
	{
	case UPLEFT:
		vertices.push_back(sf::Vector2f(right, top));
		vertices.push_back(sf::Vector2f(right, bottom));
		vertices.push_back(sf::Vector2f(left, bottom));
		break;
	case UPRIGHT:
		vertices.push_back(sf::Vector2f(left, top));
		vertices.push_back(sf::Vector2f(left, bottom));
		vertices.push_back(sf::Vector2f(right, bottom));
		
		break;
	default:
		break;
	}
}


std::vector<sf::Vector2f> PolygonCollider2D::SetTransformedVertices()
{
	if (entity->hasComponent<Transform>() && entity->hasComponent<Rigidbody>())
	{
		auto& rb = *entity->getComponent<Rigidbody>();
		const auto& transform = entity->getComponent<Transform>();
		transformedVertices.clear();
		if (rb.transformUpdateRequired)
		{
			for (auto v : vertices)
			{
				transformedVertices.push_back(vecMath.Transform(v, transform->Sin, transform->Cos, transform->position));
			}
		}
		rb.transformUpdateRequired = false;
		return transformedVertices;
	}
	return {};
}
