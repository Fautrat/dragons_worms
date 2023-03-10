#pragma once

#include "Scene.hpp"
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>
#include "../AssetManager/AssetManager.h"
#include "../UI/UI.hpp"
#include "./Menu/MenuManager.hpp"
#include "../AssetManager/AssetManager.h"

class Engine;

class MainMenuScene : public Scene
{
public:
    sf::Sprite videoSprite;
    sf::Font font;
    sf::Texture videoTexture;

    InputHandler* m_input;
    std::shared_ptr<UI> ui;
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
    void SetResolution(int width, int height);
    void Controls();
    void UpdateInput(EInput action, std::string buttonName);
    void Remap();
    void CancelRemap();
    void Volume();
    void ReduceVolume();
    void IncreaseVolume();
    void Mute();
    void Back();
    float delay = 0.0f;
    bool m_isclicked = false;
    bool m_is_remap = false;
    EInput m_actionToRemap = EInput::MoveUp;
};
