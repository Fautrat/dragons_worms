#include <string>
#include <SFML/Graphics.hpp>
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
		
		dstRect.left = transform->position.x;
		dstRect.top = transform->position.y;
		dstRect.width = width * transform->scale.x;
		dstRect.height = height * transform->scale.y;

		srcRect.left = 0;
		srcRect.top = 0;
		srcRect.width = width;
		srcRect.height = height;

		sprite = new sf::Sprite();
		sprite->setTexture(*texture);

		return true;
	}

	void draw(sf::RenderTarget* renderwindow) override final
	{
		renderwindow->draw(*sprite);
	}

	void update() override final {
		dstRect.left = static_cast<int>(transform->position.x);
		dstRect.top = static_cast<int>(transform->position.y);
		dstRect.width = static_cast<int>(width*transform->scale.x);
		dstRect.height = static_cast<int>(height*transform->scale.y);
	}

private:
	int width = 0;
	int height = 0;
	sf::Rect<int> srcRect = { 0,0,0,0 };
	sf::Rect<int> dstRect = { 0,0,0,0 };

	Transform* transform = nullptr;
	sf::Sprite* sprite;
	std::string textureID = "";
	sf::Texture* texture = nullptr;

};