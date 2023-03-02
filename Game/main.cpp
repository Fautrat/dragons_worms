#include "Engine.h"
#include <iostream>
#include <Utils/Vectormath.h>

int main()
{
    Engine* engine = Engine::getInstance();
    engine->Run();
    engine->killInstance();

    return 0;
}


