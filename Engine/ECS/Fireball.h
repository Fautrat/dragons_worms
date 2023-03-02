#pragma once

#include "Entity.h"
#include "SpriteRenderer.h"
#include "Rigidbody.h"
#include "Collider2D.h"
#include "../AssetManager/AssetManager.h"
#include "SFML/Graphics.hpp"

class Fireball : public Entity
{
public:

    Fireball(std::function<void()>& callback) : m_callback(callback)
    {
        AssetManager::get().loadTexture("Fireball", "../../../../assets/Dragon/fireball2.png");
        addComponent<Transform>().setTransform(0.f, 0.f, 0.f, 0.f, 0.5f, 0.5f);
        addComponent<SpriteRenderer>("Fireball");
        addComponent<Rigidbody>(1.f, false, 0, 0.5f);
        addComponent<Collider2D>(SPHERE, std::string("Fireball"));
    }

    Fireball(float x, float y)
    {
        AssetManager::get().loadTexture("Fireball", "../../../../assets/Dragon/fireball2.png");
        getComponent<Transform>().setTransform(x, y, 0, 0, 1.f, 1.f);
        addComponent<SpriteRenderer>("Fireball");
        addComponent<Rigidbody>(1.f, false, 0, 0.5f);
        addComponent<Collider2D>(SPHERE, std::string("Fireball"));
    }

    ~Fireball()
    {
        m_callback();
    };

private :
    std::function<void()> m_callback;
};