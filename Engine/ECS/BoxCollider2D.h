#pragma once

#include <sfml/Graphics.hpp>
#include <string>
#include "Entity.h"
#include "Component.h"

class BoxCollider2D : public Component{
public:
	BoxCollider2D(int width, int height)
	{
		box.width = width;
		box.height = height;
	}

	BoxCollider2D(int width, int height, std::string tag) : collisionTag(tag)
	{
		box.width = width;
		box.height = height;
	}

	~BoxCollider2D()
	{
		delete transform;
	}

	bool init() override final
	{
		//debugRect.setSize(sf::Vector2f(box.width, box.height));
		//debugRect.setFillColor(sf::Color::Transparent);
		//debugRect.setOutlineThickness(5);
		//debugRect.setOutlineColor(sf::Color(250, 150, 100));
		if (transform = &entity->getComponent<Transform>())
			return true;
		else
		{
			std::cout << "Problème d'initialisation component BoxCollider" << std::endl;
			return false;
		}
	}

	void draw(sf::RenderTarget* renderWindow) override final
	{
		//Debug
		//renderWindow->draw(debugRect);
		
	}

	void update() override final
	{
		box.left = transform->position.x;
		box.top = transform->position.y;
		//debugRect.setPosition(transform->position);

	}

	std::string getCollisionTag() const {
		return collisionTag;
	}

private:
	friend class Collision;
	sf::Rect<int> box = { 0,0,0,0 };
	std::string collisionTag = "";
	Transform* transform = nullptr;
	sf::RectangleShape debugRect;
	
};