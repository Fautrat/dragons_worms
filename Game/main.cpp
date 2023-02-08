#include "Game.hpp"
#include "Engine.h"
#include <iostream>

int main()
{
    /*
    Game* game = new Game();
    game->gameLoop();
    delete game;
    game = nullptr;*/
   
    Engine* engine = new Engine();
    engine->Run();
    engine->LoadScene(MAINMENU);
    delete engine;
    engine = nullptr;

    return 0;
}