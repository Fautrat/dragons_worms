#include "Game.hpp"

Game::Game()
{
    // Create the main window
    window.create(sf::VideoMode(), "Dragons", sf::Style::Fullscreen);
    window.setFramerateLimit(60);
    window.setVerticalSyncEnabled(true);

    window_width = window.getSize().x;
    window_height = window.getSize().y;

    // Load the video
    if (!videoTexture.loadFromFile("../../../../assets/wallpaper.jpg"))
    {
        std::cout << "Failed to load video" << std::endl;
        return ;
    }
    videoSprite.setTexture(videoTexture);
    videoSprite.setScale({ (float)window_width / (float)videoSprite.getTexture()->getSize().x, (float)window_height / (float)videoSprite.getTexture()->getSize().y });

    // Load the font
    font.loadFromFile("../../../../assets/font/shanghai.ttf");

    // Define the buttons
    playButton.setString("Play");
    playButton.setFont(font);
    playButton.setCharacterSize(50);
    playButton.setFillColor(sf::Color::White);
    playButton.setPosition(window_width / 3 - playButton.getGlobalBounds().width / 2, window_height / 2 - 200);

    optionsButton.setString("Options");
    optionsButton.setFont(font);
    optionsButton.setCharacterSize(50);
    optionsButton.setFillColor(sf::Color::White);
    optionsButton.setPosition(window_width / 3 - optionsButton.getGlobalBounds().width / 2, window_height / 2 - 100);

    exitButton.setString("Exit");
    exitButton.setFont(font);
    exitButton.setCharacterSize(50);
    exitButton.setFillColor(sf::Color::White);
    exitButton.setPosition(window_width / 3 - exitButton.getGlobalBounds().width / 2, window_height / 2);

    input = new InputHandler(window);
    player = new Dragon(*input);

    // define the sound
    if (!music.openFromFile("../../../../assets/sound/Dragon.ogg"))
    {
        std::cout << "Failed to load music" << std::endl;
        return;
    }
    music.setVolume(20);
}

Game::~Game()
{
    delete player;
    delete input;
    player = nullptr;
    input = nullptr;
}

void Game::gameLoop()
{   
    music.play();

    // Start the main loop
    while (window.isOpen())
    {
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

        /* handle input and update players */
        input->handleInput();
        player->update(window);

        // Clear the window
        window.clear();

        // Draw the buttons
        window.draw(videoSprite);
        window.draw(playButton);
        window.draw(optionsButton);
        window.draw(exitButton);
        window.draw(player->getShape());

        // Update the window
        window.display();
    }
}