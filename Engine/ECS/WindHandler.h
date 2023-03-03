#pragma once
#include "Entity.h"
//#include "Wind/WindComponent.h"
#include "SpriteRenderer.h"
#include <SFML/Graphics.hpp>

class WindHandler : public Entity
{
public:

    WindHandler()
    {
        AssetManager::get().loadImage("WindImage", "assets/Dragon/WindLeft.png");
        AssetManager::get().loadTexture("WindLeft", "assets/Dragon/WindLeft.png");
        addComponent<SpriteRenderer>("WindLeft");
        auto windLeftSprite = getComponent<SpriteRenderer>();
        windLeftSprite->getSprite()->setTexture(textureMask);
        windLeftSprite->getSprite()->setOrigin(0, 0);
    }

    //Int -3 to 3
    void setLevel(int value)
    {
        image = *AssetManager::get().getImage("WindImage");
        auto windLeftSprite = getComponent<SpriteRenderer>();
        sf::Color color = getComponent<SpriteRenderer>()->getSprite()->getColor();
        color.a = 0;
        windLeftSprite->getSprite()->setColor(color);

        if (value == -3)
        {
            //Nothing
            
            getComponent<Transform>()->setTransform(1920 / 2 - (windLeftSprite->getSprite()->getGlobalBounds().width * 1.2), -windLeftSprite->getSprite()->getGlobalBounds().height / 8, 0, 0, 1, 1);
        }
        else if (value == -2)
        {
            image.createMaskFromColor(sf::Color::Color(236, 28, 36), 0); //RED
            getComponent<Transform>()->setTransform(1920 / 2 - (windLeftSprite->getSprite()->getGlobalBounds().width * 1.2), -windLeftSprite->getSprite()->getGlobalBounds().height / 8, 0, 0, 1, 1);

        }
        else if (value == -1)
        {
            image.createMaskFromColor(sf::Color::Color(236, 28, 36), 0); //RED
            image.createMaskFromColor(sf::Color::Color(255, 127, 39), 0); //ORANGE
            getComponent<Transform>()->setTransform(1920 / 2 - (windLeftSprite->getSprite()->getGlobalBounds().width * 1.2), -windLeftSprite->getSprite()->getGlobalBounds().height / 8, 0, 0, 1, 1);
        }
        else if (value == 1)
        {
            image.createMaskFromColor(sf::Color::Color(236, 28, 36), 0); //RED
            image.createMaskFromColor(sf::Color::Color(255, 127, 39), 0); //ORANGE
            getComponent<Transform>()->setTransform(1920 / 2, -windLeftSprite->getSprite()->getGlobalBounds().height / 8, 0, 0, 1, 1);
        }
        else if (value == 2)
        {
            image.createMaskFromColor(sf::Color::Color(236, 28, 36), 0); //RED
            getComponent<Transform>()->setTransform(1920 / 2, -windLeftSprite->getSprite()->getGlobalBounds().height / 8, 0, 0, 1, 1);
        }
        else if (value == 3)
        {
            getComponent<Transform>()->setTransform(1920 / 2, -windLeftSprite->getSprite()->getGlobalBounds().height / 8, 0, 0, 1, 1);
        }

        if(value != 0)
        {
            if(value < 0) windLeftSprite->flipTextureRight();
            else windLeftSprite->flipTextureLeft();
            color.a = 255;
            textureMask.loadFromImage(image);
            spriteMask.setTexture(textureMask);
            windLeftSprite->getSprite()->setTexture(textureMask);
            windLeftSprite->getSprite()->setColor(color);
        }
    }
    ~WindHandler() = default;
private :
    sf::Texture textureMask;
    sf::Sprite spriteMask;
    sf::Image image;
};
