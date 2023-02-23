#include <functional>
#include <map>
#include <vector>
#include <SFML/Window.hpp>
#include "InputHandler.hpp"
#include <iostream>

void InputHandler::connect(sf::Keyboard::Key key, Slot slot)
{
    m_slots[key] = slot;
}

void InputHandler::handleInput()
{
    sf::Event event;
    while (m_window->pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            m_window->close();
        }
        else if (event.type == sf::Event::KeyPressed)
        {
            if (std::find(m_using_keys.begin(), m_using_keys.end(), event.key.code) == m_using_keys.end())
                m_using_keys.push_back(event.key.code);
        }
        else if (event.type == sf::Event::KeyReleased)
        {
            if (auto it = std::find(m_using_keys.begin(), m_using_keys.end(), event.key.code); it != m_using_keys.end())
            {
                m_using_keys.erase(it);
            }
        }
        //if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Right)
            //m_fireball.shoot(sf::Vector2f {0., 0.}, (sf::Vector2f)sf::Mouse::getPosition(m_window));

    }
    for (auto& keys : m_using_keys)
    {
        auto it = m_slots.find(keys);
        if (it != m_slots.end())
        {
            it->second();
        }
    }
}