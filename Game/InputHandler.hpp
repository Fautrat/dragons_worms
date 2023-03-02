#pragma once

#include <functional>
#include <map>
#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

enum class Action
{
    MoveUp = 0,
    MoveDown,
    MoveLeft,
    MoveRight,
    Action,
    Jump,
    Pause,
    Exit
};

class InputHandler
{
public:
    typedef std::function<void()> Slot;

    InputHandler(sf::RenderWindow* window) : m_window(window)
    {
        // set default keys azerty
        m_actions[sf::Keyboard::Z] = Action::MoveUp;
        m_actions[sf::Keyboard::S] = Action::MoveDown;
        m_actions[sf::Keyboard::Q] = Action::MoveLeft;
        m_actions[sf::Keyboard::D] = Action::MoveRight;
        m_actions[sf::Keyboard::LControl] = Action::Jump;
        m_actions[sf::Keyboard::Space] = Action::Action;
        m_actions[sf::Keyboard::Escape] = Action::Exit;
        m_actions[sf::Keyboard::Return] = Action::Pause;
        connect(Action::Exit , [this] { m_window->close(); });
    }

    void remapAction(Action action, sf::Keyboard::Key key);

    void connect(Action action, sf::Keyboard::Key key, Slot slot);

    void connect(Action action, Slot slot);
    std::string fromKtoS(const sf::Keyboard::Key& k);

    sf::Keyboard::Key getActionKey(Action action);

    void handleInput();
    ~InputHandler()
    {
        delete m_window;
        m_slots.clear();
        m_actions.clear();
    }

private:
    sf::RenderWindow* m_window;
    std::map<Action, std::function<void()>> m_slots;
    std::vector<sf::Keyboard::Key> m_using_keys;

    std::map<sf::Keyboard::Key, Action> m_actions;
};