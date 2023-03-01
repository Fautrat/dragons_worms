#pragma once

#include <iostream>
#include "InputHandler.hpp"

class Dragon
{
public:
    Dragon(InputHandler* input) : m_shape(sf::Vector2f(50.0f, 50.0f)), m_speed(5.0f)
    {
        input->connect(Action::MoveRight, [this] { m_velocity.x = m_speed; });
        input->connect(Action::MoveLeft, [this] { m_velocity.x = -m_speed; });
        input->connect(Action::Jump, [this] { m_velocity.y = -50.f; });
    }

    void update(sf::RenderTarget* window);

    sf::RectangleShape& getShape();

private:
    sf::RectangleShape m_shape;
    sf::Vector2f m_position;
    sf::Vector2f m_velocity;
    float m_speed;
};