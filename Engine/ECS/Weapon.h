#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include "Entity.h"
#include "Component.h"
#include <cmath>

class Weapon : public Component
{
public:

    Weapon() = default;
    ~Weapon() 
    {
        delete sprite;
    }

    bool init() override final {
        sprite = new sf::Sprite();
        if (nullptr != entity && nullptr != sprite)
        {
            texture.loadFromFile("../../../../assets/Dragon/fireball.png");
            sprite->setTexture(texture);
            sprite->setOrigin(sf::Vector2f(texture.getSize().x / 2, texture.getSize().y / 2));
            sprite->setScale(sf::Vector2f{ 0.1f, 0.1f });
            sprite->setPosition(entity->getComponent<Transform>().position);

            sf::Vector2f direction = static_cast<sf::Vector2f>(sf::Mouse::getPosition()) - sprite->getPosition();
            float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
            direction /= length;
            m_velocity = direction * m_speed;
            return true;
        }
        return false;
    }

    void draw(sf::RenderTarget* renderwindow) override final
    {
        renderwindow->draw(*sprite);
    }

    void update(const float& deltaTime) override final 
    {
        m_velocity.y = m_velocity.y + (9.81f * deltaTime );

        sprite->move(m_velocity * deltaTime);

        //sprite->setPosition(sprite->getPosition().x + m_velocity.x, sprite->getPosition().y + m_velocity.y);
    }

private:
    sf::Sprite* sprite = nullptr;
    sf::Texture texture;
    sf::Vector2f m_velocity;
    float m_speed = 15.f;
};