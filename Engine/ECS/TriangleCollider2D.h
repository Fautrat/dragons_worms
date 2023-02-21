#pragma once

#include "SFML/Graphics.hpp"
#include <string>
#include "Entity.h"
#include "Component.h"
#include <vector>


class TriangleCollider2D : public Component {
public:
	//First Point = 90° angle, Line Vect2 of Vect2 = {{x1,y1},{x2,y2}}
	TriangleCollider2D(sf::Vector2<sf::Vector2i> Line1, sf::Vector2<sf::Vector2i> Line2, sf::Vector2<sf::Vector2i> Line3 , int spriteWidth)
	{
		m_lines.push_back(Line1);
		m_lines.push_back(Line2);
		m_lines.push_back(Line3);
		m_spriteWidth = spriteWidth;
	}

	/*TriangleCollider2D(int firstPointx, int firstPointy, int secondPointx, int secondPointy, int thirdPointx, int thirdPointy, std::string tag) : collisionTag(tag)
	{
		pointA.x = firstPointx;
		pointA.y = firstPointy;
		pointB.x = secondPointx;
		pointB.y = secondPointy;
		pointC.x = thirdPointx;
		pointC.y = thirdPointy;
	}*/

	~TriangleCollider2D() = default;

	bool init() override final
	{
		if (transform = &entity->getComponent<Transform>())
		{
			return true;
		}
		else
		{
			std::cout << "Problème d'initialisation component TriangleCollider" << std::endl;
			return false;
		}
	}

	void draw(sf::RenderTarget* renderWindow) override final
	{

	}

	void update() override final
	{
		/*pointA.x = transform->position.x;
		pointA.y = transform->position.y;*/
	}

	std::string getCollisionTag() const {
		return collisionTag;
	}

private:
	friend class Collision;

	std::vector<sf::Vector2<sf::Vector2i>> m_lines;
	
	int m_spriteWidth = 0;


	std::string collisionTag = "";
	Transform* transform = nullptr;


};