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
	~SpriteRenderer() {
		delete transform;
		delete sprite;
		delete texture;
	}

	SpriteRenderer(std::string textureid) :textureID(textureid){}

	bool init() override final{

		if (nullptr == entity && 
			nullptr == AssetManagerTemp::get().getTexture(textureID)) 
			return false;

		transform = &entity->getComponent<Transform>();
		texture = AssetManagerTemp::get().getTexture(textureID);
		sprite = new sf::Sprite();
		if (nullptr == sprite) 
			return false;

		sprite->setTexture(*texture);
		sprite->setScale(transform->scale);
		sprite->setPosition(transform->position);
		return true;
	}

	void draw(sf::RenderTarget* renderwindow) override final
	{
		renderwindow->draw(*sprite);
	}

	void update() override final {

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
private:

	Transform* transform = nullptr;
	sf::Sprite* sprite = nullptr;
	std::string textureID = "";
	sf::Texture* texture = nullptr;

};