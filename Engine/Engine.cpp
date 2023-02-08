#include "Engine.h"

#include <iostream>

#include "../Engine/Scene/MainMenuScene.hpp"
#include "../Engine/Scene/InGameScene.hpp"
#include <iostream>


Engine* Engine::m_instance = nullptr;

Engine::Engine()
{
    gameState = RUNNING;
    m_instance = this;
    m_renderWindow = new sf::RenderWindow(
        sf::VideoMode(1920, 1080),
        "Dragons with engine",
        sf::Style::Fullscreen
    );


    m_renderWindow->setFramerateLimit(60);
    m_input = new InputHandler(m_renderWindow);
    

}

Engine::~Engine()
{
    delete m_currScene;
}

void Engine::Run()
{
    

    while (m_renderWindow->isOpen())
    {
        if (gameState == RUNNING)
        {
            sf::Time _deltaTime = m_deltaClock.restart();
            m_deltaTime = _deltaTime.asSeconds();
            //TODO INPUT MANAGER UPDATE
            m_renderWindow->clear();
        }

        if (m_currScene)
        {
            m_currScene->Update(getDeltaTime());
            m_currScene->Render(m_renderWindow);
        }

        
        HandleEvent();
        if (m_sceneToLoad != ESceneType::NONE)
            LoadScene(m_sceneToLoad);
        m_renderWindow->display();
    }



}

void Engine::ExitGame()
{
    
    gameState = STOP;
    delete m_currScene;
    m_currScene = nullptr;

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
