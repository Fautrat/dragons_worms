#pragma once

#include <functional>
#include <map>
#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

enum class EInput
{
    NONE = -1,
    MoveUp = 0,
    MoveDown,
    MoveLeft,
    MoveRight,
    Action,
    Jump,
    SelectWeapon1,
    SelectWeapon2,
    Pause,
    Exit
};

class InputHandler
{
public:
    typedef std::function<void()> Slot;

    InputHandler(sf::RenderWindow& window) : m_window(window)
    {
        // set default keys azerty
        m_actions[sf::Keyboard::Z] = EInput::MoveUp;
        m_actions[sf::Keyboard::S] = EInput::MoveDown;
        m_actions[sf::Keyboard::Q] = EInput::MoveLeft;
        m_actions[sf::Keyboard::D] = EInput::MoveRight;
        m_actions[sf::Keyboard::Num1] = EInput::SelectWeapon1;
        m_actions[sf::Keyboard::Num2] = EInput::SelectWeapon2;
        m_actions[sf::Keyboard::Space] = EInput::Jump;
        m_actions[sf::Keyboard::T] = EInput::Action;
        m_actions[sf::Keyboard::F4] = EInput::Exit;
        m_actions[sf::Keyboard::Escape] = EInput::Pause;
        connect(EInput::Exit, [this] { m_window.close(); });
    }

    void remapAction(EInput action, sf::Keyboard::Key key);

    void connect(EInput action, sf::Keyboard::Key key, Slot slot);

    void connect(EInput action, Slot slot);
    std::string fromKtoS(const sf::Keyboard::Key& k);

    sf::Keyboard::Key getActionKey(EInput action);

    void handleInput();
    ~InputHandler()
    {
        m_slots.clear();
        m_actions.clear();
    }

private:
    sf::RenderWindow& m_window;
    std::map<EInput, std::function<void()>> m_slots;
    std::vector<sf::Keyboard::Key> m_using_keys;

    std::map<sf::Keyboard::Key, EInput> m_actions;
};