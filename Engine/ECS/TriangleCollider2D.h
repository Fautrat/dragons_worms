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
			auto posX = transform->position.x - m_spriteWidth / 2;
			auto posY = transform->position.y - m_spriteWidth / 2;
			// Set all lines in the triangle 
			auto LineUPleftToUpRight = sf::Vector2(sf::Vector2i(posX, posY),
												   sf::Vector2i(posX + m_spriteWidth, posY));

			auto LineUPleftToDownLeft = sf::Vector2(sf::Vector2i(posX, posY),
													sf::Vector2i(posX, posY + m_spriteWidth));

			auto LineUPRightToDownRight = sf::Vector2(sf::Vector2i(posX + m_spriteWidth, posY),
													  sf::Vector2i(posX + m_spriteWidth, posY + m_spriteWidth));

			auto LineDownLeftToDownRight = sf::Vector2(sf::Vector2i(posX, posY + m_spriteWidth),
													   sf::Vector2i(posX + m_spriteWidth, posY + m_spriteWidth));

			auto DiagDownLeftToUpRight = sf::Vector2(sf::Vector2i(posX, posY + m_spriteWidth),
													 sf::Vector2i(posX + m_spriteWidth, posY));

			auto DiagUpLeftToDownRight = sf::Vector2(sf::Vector2i(posX, posY),
													 sf::Vector2i(posX + m_spriteWidth, posY + m_spriteWidth));
			//DownLeftByDefault
			m_lines.push_back(LineUPleftToDownLeft);
			m_lines.push_back(LineDownLeftToDownRight);
			m_lines.push_back(DiagUpLeftToDownRight);

			switch (m_angle)
			{
			case UPLEFT:
				m_lines[0] = LineUPleftToUpRight;
				m_lines[1] = LineUPleftToDownLeft;
				m_lines[2] = DiagDownLeftToUpRight;
				m_spriteRenderer->getSprite()->setRotation(90);
				break;
			case UPRIGHT:
				m_lines[0] = LineUPleftToUpRight;
				m_lines[1] = LineUPRightToDownRight;
				m_lines[2] = DiagUpLeftToDownRight;
				m_spriteRenderer->getSprite()->setRotation(180);
				break;
			case DOWNLEFT:
				m_lines[0] = LineUPleftToDownLeft;
				m_lines[1] = LineDownLeftToDownRight;
				m_lines[2] = DiagUpLeftToDownRight;
				break;
			case DOWNRIGHT:
				m_lines[0] = LineUPRightToDownRight;
				m_lines[1] = LineDownLeftToDownRight;
				m_lines[2] = DiagDownLeftToUpRight;
				m_spriteRenderer->getSprite()->setRotation(-90);
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
		//Debug
		sf::Vertex line1[] =
		{
			sf::Vertex(sf::Vector2f(m_lines[0].x.x, m_lines[0].x.y)),
			sf::Vertex(sf::Vector2f(m_lines[0].y.x, m_lines[0].y.y))
		};
		sf::Vertex line2[] =
		{
			sf::Vertex(sf::Vector2f(m_lines[1].x.x, m_lines[1].x.y)),
			sf::Vertex(sf::Vector2f(m_lines[1].y.x, m_lines[1].y.y))
		};
		sf::Vertex line3[] =
		{
			sf::Vertex(sf::Vector2f(m_lines[2].x.x, m_lines[2].x.y)),
			sf::Vertex(sf::Vector2f(m_lines[2].y.x, m_lines[2].y.y))
		};

		renderWindow->draw(line1, 2, sf::Lines);
		renderWindow->draw(line2, 2, sf::Lines);
		renderWindow->draw(line3, 2, sf::Lines);
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