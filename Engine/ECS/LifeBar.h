#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include "Entity.h"
#include "Component.h"
#include "../AssetManager/AssetManager.h"
#include <iostream>

class Dragon;

class LifeBar : public Component, public sf::Text
{
public:
	LifeBar() = default;
	~LifeBar() = default;

	bool init() override final 
	{
		if (nullptr != entity && entity->hasComponent<Transform>())
		{
			if (!AssetManager::get().getFont("Shangai"))
			{
				std::cout << "Failed to load font for life bar" << std::endl;
				return false;
			}
			font = *AssetManager::get().getFont("Shangai");
			const auto& transform = entity->getComponent<Transform>();
			setFont(font);
			setFillColor(sf::Color::Red);
			setCharacterSize(20);
			life = 100;
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
		if(entity->hasComponent<Transform>())
		{
			setString(sf::String(std::to_string(life)));
			const auto& transform = entity->getComponent<Transform>();
			const auto& spriterenderer = entity->getComponent<SpriteRenderer>();
			float posY = transform->position.y - spriterenderer->getSprite()->getGlobalBounds().height / 2.f - getGlobalBounds().height - 5.f; // léger offset
			setPosition(sf::Vector2f{ transform->position.x - getGlobalBounds().width / 2.f, posY});
		}
	}

	int life;

private:
	sf::Font font;
};