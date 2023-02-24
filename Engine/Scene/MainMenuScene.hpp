#pragma once

#include "Scene.hpp"
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>
#include "../UI/UI.hpp"

class Engine;

class MainMenuScene : public Scene
{
public:
    sf::Sprite videoSprite;
    sf::Music* music;
    sf::Texture videoTexture;

    UI* ui;

	MainMenuScene(Engine& engine);
	~MainMenuScene();

	void Start() final;
	void Update(const float& deltaTime) final;
	void Render(sf::RenderTarget* renderTarget) final;

private :
    void Play();
    void Quit();
    void Options();
    bool m_isclicked = false;
};
