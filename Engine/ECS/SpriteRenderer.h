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

struct Spark
{
    float duration;
    int repeat;
    float speed;
    float timer;
    sf::Color color;
    bool isColored = false;
    bool isActive = false;
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

        if(_spark->isActive)
        {
            SparkUpdate(deltaTime);
        }
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

    void ActiveSparks(int repeat, float speed, sf::Color color)
    {
        _spark = new Spark();
        _spark->repeat = repeat;
        _spark->speed = speed;
        _spark->color = color;
        _spark->isActive = true;
        _spark->timer = 0;
        _spark->isColored = false;
		sprite->setColor(_spark->color);
    }

    void SparkUpdate(const float& deltaTime)
    {
        if (_spark->isActive)
        {
            if (_spark->isColored)
            {
                sprite->setColor(_spark->color);
            } else
            {
                sprite->setColor(sf::Color::White);
            }
            _spark->timer += deltaTime;
            if (_spark->timer >= _spark->speed)
            {
                _spark->isColored = !_spark->isColored;
                _spark->timer = 0;
				if (_spark->isColored)_spark->repeat--;
                if (_spark->repeat <= 0)
                {
                    _spark->isActive = false;
                }
            }
        }
    }
private:
	sf::Sprite* sprite = nullptr;
	std::string textureID = "";
	sf::Texture* texture = nullptr;
	SpriteDirection sprite_dir = RIGHT;
    Spark* _spark = new Spark();
};