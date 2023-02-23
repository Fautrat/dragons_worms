#pragma once 

#include <string>
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Entity.h"
#include "Component.h"
#include "../AssetManager/AssetManager.h"

class SpriteRenderer : public Component
{
public:
	SpriteRenderer() = default;
	~SpriteRenderer() {
		delete transform;
		delete sprite;
		delete texture;
	}

	SpriteRenderer(std::string textureid) :textureID(textureid){}

	bool init() override final{
		sprite = new sf::Sprite();
		if (nullptr != entity && nullptr != AssetManager::get().getTexture(textureID) && nullptr != sprite)
		{
			transform = &entity->getComponent<Transform>();
			texture = AssetManager::get().getTexture(textureID);
			sprite->setTexture(*texture);
			sprite->setScale(transform->scale);
			sprite->setPosition(transform->position);
			sprite->setOrigin(sf::Vector2f(texture->getSize().x / 2, texture->getSize().y / 2));
			return true;
		}
		return false;
	}

	void draw(sf::RenderTarget* renderwindow) override final
	{
		renderwindow->draw(*sprite);
	}

	void update(const float& deltaTime) override final {

		sprite->setPosition(transform->position);
	}

	sf::Texture* getTexture()
	{
		return texture;
	}

	sf::Sprite* getSprite()
	{
		return sprite;
	}

	void flipTexture();
private:

	Transform* transform = nullptr;
	sf::Sprite* sprite = nullptr;
	std::string textureID = "";
	sf::Texture* texture = nullptr;

};