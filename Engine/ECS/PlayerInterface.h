#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include "Entity.h"
#include "Component.h"
#include "../AssetManager/AssetManager.h"
#include <iostream>
#include <filesystem>
class Dragon;

class PlayerInterface : public Component, public sf::Text
{
public:
	PlayerInterface() = default;
	~PlayerInterface() = default;

	bool init() override final 
	{
		//LIFEBAR
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
			setFillColor(sf::Color::White);
			setCharacterSize(20);
			life = 100;

			AssetManager::get().loadTexture("LifeBar", "assets/Dragon/lifeBar.png");
			lifeBarTexture = *AssetManager::get().getTexture("LifeBar");
			spriteLifeBar.setTexture(lifeBarTexture);
			spriteLifeBar.setScale(scaleXLifeBar, scaleYLifeBar);
			spriteLifeBar.setOrigin(lifeBarTexture.getSize().x / 2, lifeBarTexture.getSize().y / 2);
			


		//WHOPLAY
			AssetManager::get().loadTexture("Indicator", "assets/Dragon/indicatorTurn.png");
			textureWhoPlay = *AssetManager::get().getTexture("Indicator");
			spriteWhoPlay.setTexture(textureWhoPlay);
			spriteWhoPlay.setScale(0.1f, 0.1f);
			spriteWhoPlay.setOrigin(textureWhoPlay.getSize().x / 2, textureWhoPlay.getSize().y / 2);

    		// Arrow direction of cursor
    		Arrow.setSize(sf::Vector2f(5.f, 150.f));
    		Arrow.setFillColor(sf::Color::Red);

			return true;
		}
		return false;
	}

	void setIsPlaying(bool isPlaying)
	{
		this->isPlaying = isPlaying;
	}

    void draw(sf::RenderTarget* renderwindow) override final
    {

        if(isPlaying) {
            renderwindow->draw(spriteWhoPlay);

            sf::Vector2f mousePos = renderwindow->mapPixelToCoords(sf::Mouse::getPosition());
            const auto& transform = entity->getComponent<Transform>();
            Arrow.setPosition(transform->position.x, transform->position.y);
            float mouseAngle = -atan2(mousePos.x - transform->position.x, mousePos.y - transform->position.y) * 180 / 3.14159; //angle in degrees of rotation for sprite
            Arrow.setRotation(mouseAngle);

            renderwindow->draw(Arrow);
        }
        renderwindow->draw(spriteLifeBar);
        renderwindow->draw(*this);
    }

	void update(const float& deltaTime) override final 
	{
		if(entity->hasComponent<Transform>())
		{
			setString(sf::String(std::to_string(life)));
			const auto& transform = entity->getComponent<Transform>();
			float posY = transform->position.y - entity->getComponent<SpriteRenderer>()->getSprite()->getGlobalBounds().height / 2.f - getGlobalBounds().height - 6.5f; // l�ger offset
			setPosition(sf::Vector2f{ transform->position.x - getGlobalBounds().width / 2.f, posY});
			spriteWhoPlay.setPosition(transform->position.x, transform->position.y - offsetYWhoPlay);
			spriteLifeBar.setPosition(transform->position.x, transform->position.y - offsetYLifeBar);
		}
	}

	void applyDamageInterface(int damage)
	{
		life -= damage;
		
		spriteLifeBar.setScale((scaleXLifeBar * life)/100, scaleYLifeBar);

	}

	sf::Sprite* getSpriteIndicator()
	{
		return &spriteWhoPlay;
	}

	
	int life;
private:
	
	sf::Font font;
	sf::Texture textureWhoPlay;
	sf::Sprite spriteWhoPlay;
	sf::Texture lifeBarTexture;
	sf::Sprite spriteLifeBar;
    sf::RectangleShape Arrow;
	float offsetYWhoPlay = 100.f;
	float offsetYLifeBar = 55.f;
	float scaleXLifeBar = 0.7f;
	float scaleYLifeBar = 0.8f;
	bool isPlaying = false;
};