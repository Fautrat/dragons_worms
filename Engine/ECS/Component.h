#pragma once
#include <SFML/Graphics.hpp>
#include "../Utils/Vectormath.h"


class Entity;

class Component
{
public:
    Component() = default;
    virtual ~Component() = default;
    Entity* entity;
    VectorMath<float> vecMath;

    virtual bool init() { return true;};
    virtual void draw(sf::RenderTarget* renderwindow) {};
    virtual void update(const float& deltaTime) {};
};