#include "Engine.h"

#include <iostream>

#include "../Engine/Scene/MainMenuScene.h"
#include "../Engine/Scene/InGameScene.h"


Engine* Engine::m_instance = nullptr;

Engine::Engine()
    : m_window({ 1280,720 }, "DragonS")
{

    m_window.setPosition({ m_window.getPosition().x,0 });
    m_window.setFramerateLimit(60);
    m_instance = this;
}

Engine::~Engine()
{
    delete m_currScene;
}

void Engine::Run()
{
    gameState = RUNNING;
    while (m_window.isOpen())
    {
        // on traite tous les évènements de la fenêtre qui ont été générés depuis la dernière itération de la boucle
        sf::Event event;
        while (m_window.pollEvent(event))
        {
            // fermeture de la fenêtre lorsque l'utilisateur le souhaite
            if (event.type == sf::Event::Closed)
                m_window.close();
        }

        // effacement de la fenêtre en noir
        m_window.clear(sf::Color::Black);

        // c'est ici qu'on dessine tout
        // window.draw(...);

        // fin de la frame courante, affichage de tout ce qu'on a dessiné
        m_window.display();
    }
}

void Engine::ExitGame()
{
    gameState = STOP;
    delete m_currScene;
    m_currScene = nullptr;


}

void Engine::LoadScene(ESceneType scene)
{
    gameState = PAUSE;
    delete m_currScene;

    Scene* nextScene;

    switch (scene)
    {
    case MAINMENU: new MainMenuScene(*this);
        break;
    case MAINGAME: new InGameScene(*this);
        break;
    default:
        break;
    }

}

float Engine::getDeltaTime() const
{
    return m_deltaTime;
}

void Engine::HandleEvent()
{
    sf::Event e;

    while (m_window.pollEvent(e)) {
        switch (e.type) {
        case sf::Event::Closed:
            m_window.close();
            break;

        default:
            break;
        }
    }
}

void Engine::PollEvent()
{

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
