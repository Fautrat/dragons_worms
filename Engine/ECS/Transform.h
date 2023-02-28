#pragma once


#include "Component.h"
#include "SFML/Graphics.hpp"
#include <iostream>
#include <math.h>


class Transform : public Component
{
public:
    Transform() = default;

    Transform(float x, float y) {
        position.x = x;
        position.y = y;
    }

   /* Transform(sf::Vector2f position, float angle) {
        this->position.x = position.x;
        this->position.y = position.y;
        this->Sin = std::sin(angle);
        this->Cos = std::cos(angle);
    }

    Transform(float x, float y, float angle) {
        this->position.x = x;
        this->position.y = y;
        this->Sin = std::sin(angle);
        this->Cos = std::cos(angle);
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
    }*/


    void setTransform(float x, float y,float rotation,  float angle , float scalex, float scaley)
    {
        position.x = x;
        position.y = y;
        this->Sin = std::sin(angle);
        this->Cos = std::cos(angle);
        scale.x = scalex;
        scale.y = scaley;
        this->rotation = rotation;
    }

   
    void translate(sf::Vector2f v, float rotation) {
        position += v;
        this->rotation += rotation;
    }

    void moveTo(sf::Vector2f newPosition)
    {
        position = newPosition;
    }

    void Rotate(float amount)
    {
        rotation += amount;
    }


    virtual ~Transform() = default;


    float Sin;
    float Cos;
    sf::Vector2f position = sf::Vector2f();
    sf::Vector2f scale = sf::Vector2f(1.0f,1.0f);
    float rotation = 0.0f;
};