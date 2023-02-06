#include "Game.hpp"


int main()
{
    Game* game = new Game();
    game->gameLoop();
    delete game;
    game = nullptr;

    return 0;
}