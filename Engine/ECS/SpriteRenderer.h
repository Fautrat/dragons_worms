#pragma once 

#include <string>
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Entity.h"
#include "Component.h"
#include "../AssetManager/AssetManager.h"

enum SpriteDirection
{
	LEFT = 0,
	RIGHT = 1,
};

class SpriteRenderer : public Component
{
public:
	SpriteRenderer() = default;
	~SpriteRenderer() {
		delete sprite;
		delete texture;
	}

	SpriteRenderer(std::string textureid) :textureID(textureid){}


	bool init() override final{
		sprite = new sf::Sprite();
		if (nullptr != entity && nullptr != AssetManager::get().getTexture(textureID) && nullptr != sprite)
		{
			const auto& transform = entity->getComponent<Transform>();
			texture = AssetManager::get().getTexture(textureID);
			sprite->setTexture(*texture);
			sprite->setScale(transform->scale);
			sprite->setPosition(transform->position);
			sprite->setOrigin(sf::Vector2f(texture->getSize().x / 2, texture->getSize().y / 2));
			return true;
		}
		return false;
	}

	void draw(sf::RenderTarget* renderwindow) override final{
		renderwindow->draw(*sprite);
	}

	void update(const float& deltaTime) override final {
		const auto& transform = entity->getComponent<Transform>();
		sprite->setPosition(transform->position);
		sprite->setRotation(transform->rotation);
	}


	sf::Texture* getTexture(){return texture;}

	sf::Sprite* getSprite(){return sprite;}

	void flipTexture() {};

	void flipTextureLeft()
	{
		if (sprite_dir == RIGHT)
		{
			sprite->setTextureRect(sf::IntRect(sprite->getTextureRect().width, 0, -sprite->getTextureRect().width, sprite->getTextureRect().height));
			sprite_dir = LEFT;
		}
	}

	void flipTextureRight()
	{
		if (sprite_dir == LEFT)
		{
			sprite->setTextureRect(sf::IntRect(0, 0, -sprite->getTextureRect().width, sprite->getTextureRect().height));
			sprite_dir = RIGHT;
		}
	}

private:
	sf::Sprite* sprite = nullptr;
	std::string textureID = "";
	sf::Texture* texture = nullptr;
	SpriteDirection sprite_dir = RIGHT;
};