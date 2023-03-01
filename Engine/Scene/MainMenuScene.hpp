#pragma once

#include "Scene.hpp"
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>
#include "../../Game/dragons.hpp"
#include "../UI/UI.hpp"
#include "./Menu/MenuManager.hpp"

class Engine;

class MainMenuScene : public Scene
{
public:
    sf::Sprite videoSprite;
    sf::Music* music;
    sf::Font font;
    sf::Texture videoTexture;

    InputHandler* m_input;
    UI* ui;
    MenuManager* menuManager;

	MainMenuScene(Engine& engine);
	~MainMenuScene();

	void Start() final;
	void Update(const float& deltaTime) final;
	void Render(sf::RenderTarget* renderTarget) final;

private :
    void Play();
    void Quit();
    void Options();
    void Resolution();
    void Controls();
    void Volume();
    void Back();
    void SetResolution(int width, int height);
    float delay = 0.0f;
    bool m_isclicked = false;
};
