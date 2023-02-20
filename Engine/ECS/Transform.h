#pragma once
#include "Component.h"
#include "SFML/Graphics.hpp"
#include <iostream>

class Transform : public Component
{
public:
    Transform() = default;

    Transform(float x, float y) {
        position.x = x;
        position.y = y;
    }

    Transform(float x, float y, float scalex, float scaley) {
        position.x = x;
        position.y = y;
        scale.x = scalex;
        scale.y = scaley;
    }

    Transform(float x, float y, float scalex, float scaley, float rotation) {
        position.x = x;
        position.y = y;
        scale.x = scalex;
        scale.y = scaley;
        this->rotation = rotation;
    }
    virtual ~Transform() = default;

    void translate(sf::Vector2f v) {
        position += v;
    }


    
    sf::Vector2f position = sf::Vector2f();
    sf::Vector2f scale = sf::Vector2f(1.0f,1.0f);
    float rotation = 0.0f;
};