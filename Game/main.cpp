#include "dragons.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <iostream>


int main()
{
    // Create the main window
    sf::RenderWindow window(sf::VideoMode(1600, 900), "Dragons");
    window.setFramerateLimit(60);
    window.setVerticalSyncEnabled(true);

    unsigned int window_width = window.getSize().x;
    unsigned int window_height = window.getSize().y;

    // Load the video
    sf::Texture videoTexture;
    if (!videoTexture.loadFromFile("../../../../assets/wallpaper.jpg"))
    {
        std::cout << "Failed to load video" << std::endl;
        return -1;
    }
    sf::Sprite videoSprite(videoTexture);
    videoSprite.setScale({ (float)window_width / (float)videoSprite.getTexture()->getSize().x, (float)window_height / (float)videoSprite.getTexture()->getSize().y });

    // Load the font
    sf::Font font;
    font.loadFromFile("../../../../assets/font/shanghai.ttf");

    // Define the buttons
    sf::Text playButton;
    playButton.setString("Play");
    playButton.setFont(font);
    playButton.setCharacterSize(50);
    playButton.setFillColor(sf::Color::White);
    playButton.setPosition(window_width / 3 - playButton.getGlobalBounds().width / 2, window_height / 2 - 200);

    sf::Text optionsButton;
    optionsButton.setString("Options");
    optionsButton.setFont(font);
    optionsButton.setCharacterSize(50);
    optionsButton.setFillColor(sf::Color::White);
    optionsButton.setPosition(window_width / 3 - optionsButton.getGlobalBounds().width / 2, window_height / 2 - 100);

    sf::Text exitButton;
    exitButton.setString("Exit");
    exitButton.setFont(font);
    exitButton.setCharacterSize(50);
    exitButton.setFillColor(sf::Color::White);
    exitButton.setPosition(window_width / 3 - exitButton.getGlobalBounds().width / 2, window_height / 2);

    // define the sound
    sf::Music music;
    if (!music.openFromFile("../../../../assets/sound/Dragon.ogg"))
        return -1; // erreur
    music.setVolume(50);
    music.play();

    // Start the main loop
    while (window.isOpen())
    {
        // Check for events
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }

        // Check if the buttons are clicked
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        if (playButton.getGlobalBounds().contains(mousePos.x, mousePos.y))
        {
            playButton.setFillColor(sf::Color::Red);
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                // Handle the "Play" button click event
                std::cout << "Play button clicked" << std::endl;
            }
        }
        else
        {
            playButton.setFillColor(sf::Color::White);
        }

        if (optionsButton.getGlobalBounds().contains(mousePos.x, mousePos.y))
        {
            optionsButton.setFillColor(sf::Color::Red);
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                // Handle the "Options" button click event
                std::cout << "Options button clicked" << std::endl;
            }
        }
        else
        {
            optionsButton.setFillColor(sf::Color::White);
        }
        if (exitButton.getGlobalBounds().contains(mousePos.x, mousePos.y))
        {
            exitButton.setFillColor(sf::Color::Red);
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                // Handle the "Exit" button click event
                std::cout << "Exit button clicked" << std::endl;
                window.close();
            }
        }
        else
        {
            exitButton.setFillColor(sf::Color::White);
        }

        // Clear the window
        window.clear();

        // Draw the buttons
        window.draw(videoSprite);
        window.draw(playButton);
        window.draw(optionsButton);
        window.draw(exitButton);


        // Update the window
        window.display();
    }

    return 0;
}