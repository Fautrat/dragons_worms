#pragma once

#include <sfml/Graphics.hpp>
#include <string>
#include "Entity.h"
#include "Component.h"
#include "SpriteRenderer.h"
#include "RigidBody.h"
#include "../Utils/Vectormath.h"
#include "../Physics/ECollisionType.h"
#include <memory>

class PolygonCollider2D : public Component
{
public:
	PolygonCollider2D() = default;
	PolygonCollider2D(ColliderType col) : colType(col) {};
	PolygonCollider2D(std::string tag) : collisionTag(tag) {}

	~PolygonCollider2D() {
		delete transform;
		delete rb;
	}

	bool init() override final;

	void CreateBoxVertices(float width, float height);
	void CreateTriangleVertices(float width, float height);
	//void CreateBoxTriangles();
	void draw(sf::RenderTarget* renderWindow) override final {}

	void update(const float& deltaTime) override final
	{
		SetTransformedVertices();
	}

	std::vector<sf::Vector2f> SetTransformedVertices();

	std::string getCollisionTag() const {
		return collisionTag;
	}

private:
	bool canGetVertices = false;
	friend class Collision;
	std::vector<sf::Vector2f> transformedVertices;
	std::string collisionTag = "";
	std::vector<sf::Vector2f> vertices;
	//std::vector<int> Triangles;
	int width = 0;
	int height = 0;
	Transform* transform = nullptr;
	Rigidbody* rb = nullptr;
	ColliderType colType;
	
};