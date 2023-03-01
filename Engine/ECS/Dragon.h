#pragma once

#include "Entity.h"
#include "EntityManager.h"
#include "../../Game/InputHandler.hpp"
#include "SpriteRenderer.h"
#include "Rigidbody.h"
#include "Weapon.h"
#include "Fireball.h"
#include "SFML/Graphics.hpp"

class Dragon : public Entity
{
public:

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

    void connectInput(InputHandler* input, EntityManager& manager)
    {
        input->connect(sf::Keyboard::D, [this] {getComponent<Rigidbody>().moveHorizontal(1); getComponent<SpriteRenderer>().flipTextureRight(); });
        input->connect(sf::Keyboard::Q, [this] {getComponent<Rigidbody>().moveHorizontal(-1); getComponent<SpriteRenderer>().flipTextureLeft(); });
        input->connect(sf::Keyboard::N, [&manager, this] 
            {
                Fireball* f = new Fireball(getComponent<Transform>().position.x, getComponent<Transform>().position.y);
                sf::Vector2f direction = static_cast<sf::Vector2f>(sf::Mouse::getPosition()) - getComponent<Transform>().position;
                float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
                direction /= length;
                direction *= 10.f;
                f->getComponent<Rigidbody>().setVelocity(direction);
                printf("%f", f->getComponent<Rigidbody>().getVelocity().x);
                manager.addEntity(f); 
            });
        input->connect(sf::Keyboard::Space, [this] {getComponent<Rigidbody>().Jump(); });
    }

private:
    unsigned int life = 100;
};