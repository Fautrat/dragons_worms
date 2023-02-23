#include <string>
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Entity.h"
#include "Component.h"
#include "../AssetManagerTemp/AssetManagerTemp.h"

class SpriteRenderer : public Component
{
public:
	SpriteRenderer() = default;
	virtual ~SpriteRenderer() = default;
	SpriteRenderer(std::string textureid) :textureID(textureid){}

	bool init() override final{

		if(nullptr != entity)
		transform = &entity->getComponent<Transform>();
		texture = AssetManagerTemp::get().getTexture(textureID);

		sprite = new sf::Sprite();
		sprite->setTexture(*texture);
		sprite->setScale(transform->scale);
		sprite->setPosition(transform->position);
		return true;
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
	sf::Sprite* sprite;
	std::string textureID = "";
	sf::Texture* texture = nullptr;

};