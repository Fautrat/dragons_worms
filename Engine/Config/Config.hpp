#pragma once
#include <string>
#include <vector>
#include <map>
#include <SFML/Graphics.hpp>



class Config {
public:
    static Config& getInstance() {
        static Config instance;
        return instance;
    }

    Config(Config const&) = delete;
    void operator=(Config const&) = delete;

    int getScreenWidth() const;
    int getScreenHeight() const;

    std::map<std::string, sf::Keyboard::Key> getKeys() const;
    std::map<std::string, sf::Mouse::Button> getMouseButtons() const;

private:
    Config();
    ~Config();

    int screenWidth;
    int screenHeight;

    std::map<std::string, sf::Keyboard::Key> keys;
    std::map<std::string, sf::Mouse::Button> mouseButtons;
};

