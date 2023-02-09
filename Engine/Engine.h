#pragma once

#include <sfml/graphics.hpp>
#include <memory>
#include <vector>
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
public:
	Engine();
	~Engine();
	void Run();
	void ExitGame();
	void LoadScene(ESceneType scene);
	static Engine& getInstance();
	sf::RenderWindow& getRenderWindow();
	const EState& getGameState() const;
	InputHandler& getInputHandler();
	sf::Vector2<int> getMousePos();
	void setSceneToLoad(ESceneType scene);

private:
	EState gameState = STOP;
	sf::RenderWindow* m_renderWindow = nullptr;
	InputHandler* m_input;
	float m_deltaTime = 0;
	float getDeltaTime() const;

	void HandleEvent();

	ESceneType m_sceneToLoad = ESceneType::MAINMENU;
	static Engine* m_instance;
	Scene* m_currScene = nullptr;
	sf::RenderWindow m_window;
	sf::Clock m_deltaClock;
	sf::Vector2<int> m_mousePosition;
};