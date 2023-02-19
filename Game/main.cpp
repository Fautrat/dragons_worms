#include "Engine.h"
#include <iostream>                             

int main()
{
    Engine* engine = Engine::getInstance();
    engine->Run();


    return 0;
}