#pragma once
#include <SFML/Graphics.hpp>

class Entity;

class Component
{
public:
    Component() = default;
    virtual ~Component() = default;
    Entity* entity;

    virtual bool init() { return true;};
    virtual void draw(sf::RenderTarget* renderwindow) {};
    virtual void update() {};
};