#include "Engine.h"

#include <iostream>

#include "../Engine/Scene/MainMenuScene.hpp"
#include "../Engine/Scene/InGameScene.hpp"






Engine* Engine::m_instance = nullptr;

Engine::Engine()
{
    gameState = RUNNING;
    m_instance = this;
    m_renderWindow = new sf::RenderWindow(
        sf::VideoMode(1920, 1080),
        "Dragons with engine",
        sf::Style::Resize
    );
    m_renderWindow->setFramerateLimit(60);
    m_input = new InputHandler(m_renderWindow);


}

Engine::~Engine()
{
    delete m_currScene;
    m_currScene = nullptr;
}

void Engine::Run()
{
    while (m_renderWindow->isOpen())
    {
        
        if (gameState == RUNNING)
        {
            sf::Time _deltaTime = m_deltaClock.restart();
            m_deltaTime = _deltaTime.asSeconds();
           
            HandleEvent();
            
            if (nullptr != m_currScene)
            {
                m_mousePosition = sf::Mouse::getPosition();
                m_currScene->Update(getDeltaTime());
                m_renderWindow->clear();
                m_currScene->Render(m_renderWindow);
                m_renderWindow->display();
            }
            
            if (m_sceneToLoad != ESceneType::NONE)
                LoadScene(m_sceneToLoad);
            
        }
    }
}

void Engine::ExitGame()
{
    gameState = STOP;
    //AssetManagerTemp::get().clean();
    if(m_renderWindow)
    m_renderWindow->close();
}

void Engine::LoadScene(ESceneType scene)
{
    std::cout << "Loadscene" << std::endl;
    gameState = PAUSE;
    delete m_currScene;

    Scene* nextScene;

    switch (scene)
    {
    case MAINMENU: nextScene = new MainMenuScene(*this);
        break;
    case MAINGAME: nextScene = new InGameScene(*this);
        break;
    default:
        break;
    }

    m_currScene = nextScene;

    m_sceneToLoad = ESceneType::NONE;
    gameState = RUNNING;
    m_currScene->Start();
}

float Engine::getDeltaTime() const
{
    return m_deltaTime;
}

void Engine::HandleEvent()
{
    m_input->handleInput();
}

InputHandler& Engine::getInputHandler()
{
    return *m_input;
}

sf::Vector2<int> Engine::getMousePos()
{
    return m_mousePosition;
}

void Engine::setSceneToLoad(ESceneType scene)
{
    m_sceneToLoad = scene;
}


Engine& Engine::getInstance() {
    return *m_instance;
}

sf::RenderWindow& Engine::getRenderWindow()
{
    // TODO: insérer une instruction return ici 
    return *m_renderWindow;
}

const EState& Engine::getGameState() const
{
    return gameState;
}
