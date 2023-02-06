#include <functional>
#include <map>
#include <vector>
#include <SFML/Window.hpp>
#include "InputHandler.hpp"

void InputHandler::connect(sf::Keyboard::Key key, Slot slot)
{
    m_slots[key] = slot;
}

void InputHandler::handleInput()
{
    sf::Event event;
    while (m_window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            m_window.close();
        }
        else if (event.type == sf::Event::KeyPressed)
        {
            auto it = m_slots.find(event.key.code);
            if (it != m_slots.end())
            {
                it->second();
            }
        }
    }
}