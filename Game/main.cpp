#include "Engine.h"
#include <iostream>

int main()
{
    Engine* engine = new Engine();
    engine->Run();
    delete engine;
    engine = nullptr;

    return 0;
}