#pragma once

#include "Scene.hpp"
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>
#include "../../Game/dragons.hpp"
#include "../UI/UI.hpp"

class Engine;

class MainMenuScene : public Scene
{
public:
  
    sf::Sprite videoSprite;
    sf::Text playButton;
    sf::Text optionsButton;
    sf::Text exitButton;
    sf::Music music;

    sf::Font font;
    sf::Texture videoTexture;

    InputHandler* m_input;
    UI* ui;

	MainMenuScene(Engine& engine);
	~MainMenuScene();

	void Start() final;
	void Update(const float& deltaTime) final;
	void Render(sf::RenderTarget* renderTarget) final;

    unsigned int window_width;
    unsigned int window_height;
};
