#pragma once

#include <functional>
#include <map>
#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

class InputHandler
{
public:
    typedef std::function<void()> Slot;

    InputHandler(sf::RenderWindow* window) : m_window(window)
    {
        connect(sf::Keyboard::Escape, [this] { m_window->close(); });
    }

    void connect(sf::Keyboard::Key key, Slot slot);

    void handleInput();
    ~InputHandler()
    {
        delete m_window;
    }

private:
    sf::RenderWindow* m_window;
    std::map<sf::Keyboard::Key, std::function<void()>> m_slots;
};