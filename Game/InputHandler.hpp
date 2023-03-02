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

    InputHandler(sf::RenderWindow& window) : m_window(window)
    {
        connect(sf::Keyboard::Escape, [this] {m_window.close();});
    }

    void connect(sf::Keyboard::Key key, Slot slot);

    /*size_t connect(const Slot& slot) const
    {
        m_slots.insert({ ++m_currentId, slot });
        return m_currentId;
    }*/

    /*template<typename ObjectType>
    size_t connect(ObjectType* pInstance, void (ObjectType::* func)()) const
    {
        return connect([=]()
        {
            (pInstance->*func)();
        });
    }*/

    /*void disconnectAll() const;

    void disconnect(const size_t& id) const;*/

    void handleInput();
    ~InputHandler() = default;

private:
    sf::RenderWindow& m_window;
    mutable std::map<sf::Keyboard::Key, std::function<void()>> m_slots;
    //mutable size_t m_currentId;
    std::vector<sf::Keyboard::Key> m_using_keys;
};