#include "Engine.h"
#include <iostream>
#include <Utils/Vectormath.h>

int main()
{
    Engine* engine = Engine::getInstance();
    engine->Run();

    return 0;
}


