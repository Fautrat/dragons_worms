#include "Engine.h"
#include <iostream>
#include "ECS/Input.h"

int main()
{
    Engine* engine = Engine::getInstance();
    engine->Run();

    return 0;
}