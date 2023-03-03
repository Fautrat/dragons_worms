#pragma once

#include <sfml/graphics.hpp>
#include <memory>
#include <vector>
#include <mutex>
#include "../Game/InputHandler.hpp"


enum EState {
	STOP = 1,
	RUNNING,
	PAUSE
};

enum ESceneType {
	MAINMENU = 1,
	MAINGAME,
	NONE
};

class Scene;


class Engine
{
protected:
	Engine();
	~Engine();
public:
	void Run();
	void ExitGame();
	static Engine* getInstance();
	static void killInstance();
    const EState& getGameState() const;
    void setGameState(EState state);
	Engine(Engine& other) = delete;
	void operator=(const Engine&) = delete;

	//Scenes
	void LoadScene(ESceneType scene);
	void setSceneToLoad(ESceneType scene);

    // Resolution
    void setResolution(int width, int height);
    void setResolution(sf::Vector2<int> resolution);
    [[nodiscard]] sf::Vector2<int> getResolution() const;


    sf::RenderWindow& getRenderWindow();
	sf::Vector2<int> getMousePos();
	InputHandler& getInputHandler();

private:
	static std::mutex m_mutex;
	static Engine* m_instance;

	EState gameState = STOP;
	//Scenes
	ESceneType m_sceneToLoad = ESceneType::MAINMENU;
	Scene* m_currScene = nullptr;

	InputHandler* m_input;
	sf::RenderWindow* m_renderWindow = nullptr;

	float m_deltaTime = 0;
	float getDeltaTime() const;
	void HandleEvent();

	
	sf::Clock m_deltaClock;
	sf::Vector2<int> m_mousePosition;
    sf::Vector2<int> m_resolution = { 1280, 720 };
};