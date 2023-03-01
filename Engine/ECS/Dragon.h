#pragma once

#include "Entity.h"
#include "../../Game/InputHandler.hpp"
#include "SpriteRenderer.h"
#include "Rigidbody.h"
#include "Weapon.h"
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

    void connectInput(InputHandler* input)
    {
        input->connect(sf::Keyboard::D, [this] {getComponent<Rigidbody>().moveHorizontal(1); getComponent<SpriteRenderer>().flipTextureRight(); });
        input->connect(sf::Keyboard::Q, [this] {getComponent<Rigidbody>().moveHorizontal(-1); getComponent<SpriteRenderer>().flipTextureLeft(); });
        input->connect(sf::Keyboard::N, [this] {addComponent<Weapon>(); });
        input->connect(sf::Keyboard::Space, [this] {getComponent<Rigidbody>().Jump(); });
    }

private:
    unsigned int life = 100;
};