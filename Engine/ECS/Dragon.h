#pragma once

#include "Entity.h"
#include "EntityManager.h"
#include "../../Game/InputHandler.hpp"
#include "SpriteRenderer.h"
#include "Rigidbody.h"
#include "Fireball.h"
#include "LifeBar.h"
#include "SFML/Graphics.hpp"
#include <functional>

class Dragon : public Entity
{
public:

    Dragon()
    {
        AssetManager::get().loadTexture("Player", "assets/Dragon/dragon.png");
        getComponent<Transform>()->scale = sf::Vector2f(0.7f, 0.7f);
        addComponent<SpriteRenderer>("Player");
        addComponent<Rigidbody>(1, false, 0, 2);
        addComponent<Collider2D>(BOX, std::string("Player"));
        addComponent<LifeBar>();
        turnEnding = false;
        hasShoot = false;
    }

    ~Dragon() = default;

    const int getLife()
    {
        return getComponent<LifeBar>()->life;
    }

    void takeDamage(int damage)
    {
        getComponent<LifeBar>()->life -= damage;
        //life -= damage;

        /* if (life <= 0) is dead */
    }

    void connectInput(InputHandler* input)
    {
        input->connect(sf::Keyboard::D, [this] {getComponent<Rigidbody>()->moveHorizontal(1); getComponent<SpriteRenderer>()->flipTextureRight(); });
        input->connect(sf::Keyboard::Q, [this] {getComponent<Rigidbody>()->moveHorizontal(-1); getComponent<SpriteRenderer>()->flipTextureLeft(); });
        input->connect(sf::Keyboard::N, [this, &input]
            {
                const auto fireball = shoot();
                if (fireball)
                {
                    //auto entity = static_cast<Entity*>(fireball);
                    EntityManager::getInstance()->addEntity(fireball);
                }
            });
        input->connect(sf::Keyboard::Space, [this] {getComponent<Rigidbody>()->Jump(); });
    }

    Fireball* shoot()
    {
        if (hasShoot)
            return nullptr;

        /* calcul de direction */
        sf::Vector2f direction = static_cast<sf::Vector2f>(sf::Mouse::getPosition()) - getComponent<Transform>()->position;
        float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
        direction /= length;
        direction *= 10.f;

        sf::Vector2f newPos (getComponent<Transform>()->position.x, getComponent<Transform>()->position.y );
        if (direction.x <= 0)
            newPos.x -= getComponent<SpriteRenderer>()->getSprite()->getGlobalBounds().width - 1.f;
        else
            newPos.x += getComponent<SpriteRenderer>()->getSprite()->getGlobalBounds().width + 1.f;
        std::function<void()> callback = [this] {endTurn();};
        Fireball* fireball = new Fireball(callback, true);
        if (direction.x <= 0)
        {
            fireball->getComponent<SpriteRenderer>()->flipTextureLeft();
        }

        fireball->getComponent<Transform>()->moveTo(newPos);
        fireball->getComponent<Rigidbody>()->setVelocity(direction);
        hasShoot = true;

        return fireball;
    }

    void endTurn()
    {
        turnEnding = true;
    }

    bool turnEnding;
    bool hasShoot;
};