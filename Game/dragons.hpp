#pragma once

#include <iostream>
#include "InputHandler.hpp"

class Dragon
{
public:
    Dragon(InputHandler* input) : m_shape(sf::Vector2f(50.0f, 50.0f)), m_speed(5.0f)
    {
        input->connect(sf::Keyboard::D, [this] { m_velocity.x = m_speed; });
        input->connect(sf::Keyboard::Q, [this] { m_velocity.x = -m_speed; });
        input->connect(sf::Keyboard::Space, [this] { m_velocity.y = -50.f; });
    }

    void update(sf::RenderTarget* window);

    sf::RectangleShape& getShape();

private:
    sf::RectangleShape m_shape;
    sf::Vector2f m_position;
    sf::Vector2f m_velocity;
    float m_speed;
};