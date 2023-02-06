#include "dragons.hpp"

void Dragon::update(sf::RenderWindow& window)
{
    /* max velocity at 50.f for debug */
    if (m_velocity.y < 20.f)
        m_velocity.y += 5.0f;

    m_position += m_velocity;

    // keep the character within the window bounds
    auto size = m_shape.getSize();
    auto windowSize = window.getSize();

    if (m_position.x < 0)
    {
        m_position.x = 0;
    }
    else if (m_position.x + size.x > windowSize.x)
    {
        m_position.x = windowSize.x - size.x;
    }

    if (m_position.y < 0)
    {
        m_position.y = 0;
    }
    else if (m_position.y + size.y > windowSize.y)
    {
        m_position.y = windowSize.y - size.y;
    }

    m_shape.setPosition(m_position);
    m_velocity *= 0.95f;
}

sf::RectangleShape& Dragon::getShape()
{
    return m_shape;
}