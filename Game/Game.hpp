#pragma once
#include "Dragons.hpp"
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>
#include <iostream>

class Game
{
public:

    sf::RenderWindow* window;
    sf::Sprite videoSprite;
    sf::Text playButton;
    sf::Text optionsButton;
    sf::Text exitButton;
    sf::Music music;

    sf::Font font;
    sf::Texture videoTexture;

    InputHandler* input;
    Dragon* player;

public:

    Game();
    ~Game();

    /* Main loop of the game. */
    void gameLoop();

    unsigned int window_width;
    unsigned int window_height;

};