#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include "Entity.h"
#include "Component.h"
#include <iostream>

class LifeBar : public Component, public sf::Text
{
public:
	LifeBar() = default;
	~LifeBar() {
		delete transform;
	}

	bool init() override final 
	{
		if (nullptr != entity)
		{
			if (!font.loadFromFile("../../../../assets/font/shanghai.ttf"))
			{
				std::cout << "Failed to load font" << std::endl;
				return false;
			}
			transform = &entity->getComponent<Transform>();
			setFont(font);
			setFillColor(sf::Color::Red);
			setCharacterSize(20);
			//setOrigin(transform->position);
			setPosition(sf::Vector2f{ transform->position.x, transform->position.y - 80 });
			setString("100");
			return true;
		}
		return false;
	}

	void draw(sf::RenderTarget* renderwindow) override final
	{
		renderwindow->draw(*this);
	}

	void update(const float& deltaTime) override final 
	{
		setPosition(sf::Vector2f{ transform->position.x, transform->position.y - 80 });
	}

private:

	Transform* transform = nullptr;
	sf::Font font;
};