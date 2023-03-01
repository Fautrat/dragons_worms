#pragma once

#include "Entity.h"
#include "EntityManager.h"
#include "../../Game/InputHandler.hpp"
#include "SpriteRenderer.h"
#include "Rigidbody.h"
#include "Weapon.h"
#include "Fireball.h"
#include "LifeBar.h"
#include "../Physics/World.h"
#include "SFML/Graphics.hpp"

class Dragon : public Entity
{
public:

    Dragon()
    {
        AssetManager::get().loadTexture("Player", "../../../../assets/Dragon/dragon.png");
        getComponent<Transform>().scale = sf::Vector2f(0.7f, 0.7f);
        addComponent<SpriteRenderer>("Player");
        addComponent<Rigidbody>(1, false, 0, 2);
        addComponent<Collider2D>(BOX, std::string("Player"));
        addComponent<LifeBar>();
    }

    ~Dragon() = default;

    const unsigned int getLife() const
    {
        return life;
    }

    void takeDamage(unsigned int damage)
    {
        life -= damage;

        /* if (life <= 0) is dead */
    }

    void connectInput(InputHandler* input, EntityManager& manager, World& worldPhysics)
    {
        input->connect(sf::Keyboard::D, [this] {getComponent<Rigidbody>().moveHorizontal(1); getComponent<SpriteRenderer>().flipTextureRight(); });
        input->connect(sf::Keyboard::Q, [this] {getComponent<Rigidbody>().moveHorizontal(-1); getComponent<SpriteRenderer>().flipTextureLeft(); });
        input->connect(sf::Keyboard::N, [&manager, this, &worldPhysics] 
            {
                const auto fireball = this->shoot();
                if (fireball)
                {
                    auto entity = dynamic_cast<Entity*>(fireball);
                    worldPhysics.addEntityWithPhysics(*entity);
                    manager.addEntity(entity);
                }
            });
        input->connect(sf::Keyboard::Space, [this] {getComponent<Rigidbody>().Jump(); });
    }

    Fireball* shoot()
    {
        /* calcul de direction */
        sf::Vector2f direction = static_cast<sf::Vector2f>(sf::Mouse::getPosition()) - getComponent<Transform>().position;
        float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
        direction /= length;
        direction *= 10.f;

        sf::Vector2f newPos (getComponent<Transform>().position.x, getComponent<Transform>().position.y);
        Fireball* fireball = new Fireball();
        if (direction.x <= 0)
        {
            newPos.x += getComponent<SpriteRenderer>().getSprite()->getGlobalBounds().width;
            fireball->getComponent<SpriteRenderer>().flipTextureLeft();
        }
        else
        {
            newPos.x += getComponent<SpriteRenderer>().getSprite()->getGlobalBounds().width;
        }

        if (direction.y <= 0)
        {
            newPos.y -= getComponent<SpriteRenderer>().getSprite()->getGlobalBounds().height;
        }
        else
        {
            newPos.y += getComponent<SpriteRenderer>().getSprite()->getGlobalBounds().height;
        }
        fireball->getComponent<Transform>().moveTo(newPos);
        fireball->getComponent<Rigidbody>().setVelocity(direction);
        
        auto fi = fireball->getComponent<Collider2D>().getCollisionTag();

        return fireball;
    }

private:
    unsigned int life = 100;
};