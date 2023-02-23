#pragma once

#include "SFML/Graphics.hpp"
#include <string>
#include "Entity.h"
#include "Component.h"
#include <vector>
#include "SpriteRenderer.h"

// The angle side is the position of the 90° angle of the triangle
enum AngleSide{
	UPLEFT,
	UPRIGHT,
	DOWNLEFT,
	DOWNRIGHT
};

class TriangleCollider2D : public Component {
public:
	//First Point = 90° angle, Line Vect2 of Vect2 = {{x1,y1},{x2,y2}}
	TriangleCollider2D(sf::Vector2<sf::Vector2i> Line1, sf::Vector2<sf::Vector2i> Line2, sf::Vector2<sf::Vector2i> Line3 , int spriteWidth)
	{

	}

	TriangleCollider2D(int spriteWidth, AngleSide angle) : m_spriteWidth(spriteWidth), m_angle(angle)
	{
		
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

	~TriangleCollider2D()
	{
		delete transform;
	};

	bool init() override final
	{
		transform = &entity->getComponent<Transform>();
		m_spriteRenderer = &entity->getComponent<SpriteRenderer>();
		if(transform && m_spriteRenderer)
		{
			// Set all lines in the triangle 
			auto LineUPleftToUpRight = sf::Vector2(sf::Vector2i(transform->position.x, transform->position.y),
				sf::Vector2i(transform->position.x + m_spriteWidth, transform->position.y));

			auto LineUPleftToDownLeft = sf::Vector2(sf::Vector2i(transform->position.x, transform->position.y),
				sf::Vector2i(transform->position.x, transform->position.y + m_spriteWidth));

			auto LineUPRightToDownRight = sf::Vector2(sf::Vector2i(transform->position.x + m_spriteWidth, transform->position.y),
				sf::Vector2i(transform->position.x + m_spriteWidth, transform->position.y + m_spriteWidth));

			auto LineDownLeftToDownRight = sf::Vector2(sf::Vector2i(transform->position.x, transform->position.y + m_spriteWidth),
				sf::Vector2i(transform->position.x + m_spriteWidth, transform->position.y + m_spriteWidth));

			auto DiagDownLeftToUpRight = sf::Vector2(sf::Vector2i(transform->position.x, transform->position.y + m_spriteWidth),
				sf::Vector2i(transform->position.x + m_spriteWidth, transform->position.y));

			auto DiagUpLeftToDownRight = sf::Vector2(sf::Vector2i(transform->position.x, transform->position.y),
				sf::Vector2i(transform->position.x + m_spriteWidth, transform->position.y + m_spriteWidth));

			switch (m_angle)
			{
			case UPLEFT:
				m_lines.push_back(LineUPleftToUpRight);
				m_lines.push_back(LineUPleftToDownLeft);
				m_lines.push_back(DiagDownLeftToUpRight);
				m_spriteRenderer->getSprite()->setRotation(90);
				transform->position.x += m_spriteWidth;
				break;
			case UPRIGHT:
				m_lines.push_back(LineUPleftToUpRight);
				m_lines.push_back(LineUPRightToDownRight);
				m_lines.push_back(DiagUpLeftToDownRight);
				m_spriteRenderer->getSprite()->setRotation(180);
				transform->position.x += m_spriteWidth;
				transform->position.y += m_spriteWidth;
				break;
			case DOWNLEFT:
				m_lines.push_back(LineUPleftToDownLeft);
				m_lines.push_back(LineDownLeftToDownRight);
				m_lines.push_back(DiagUpLeftToDownRight);
				break;
			case DOWNRIGHT:
				m_lines.push_back(LineUPRightToDownRight);
				m_lines.push_back(LineDownLeftToDownRight);
				m_lines.push_back(DiagDownLeftToUpRight);
				m_spriteRenderer->getSprite()->setRotation(-90);
				transform->position.y += m_spriteWidth;
				break;
			default:
				break;
			}

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

	AngleSide m_angle = DOWNLEFT;
	std::string collisionTag = "";
	Transform* transform = nullptr;
	SpriteRenderer* m_spriteRenderer = nullptr;


};