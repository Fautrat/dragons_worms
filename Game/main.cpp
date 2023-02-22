#include "Engine.h"
#include <iostream>
#include "ECS/Input.h"
#include "ECS/SphereCollider2D.h"
#include "ECS/TriangleCollider2D.h"

int main()
{
    Engine* engine = Engine::getInstance();
    engine->Run();


    return 0;
}

 Projectiletest.cpp : Defines the entry point for the console application.


