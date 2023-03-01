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

    Fireball(float x, float y)
    {
        AssetManager::get().loadTexture("Fireball", "../../../../assets/Dragon/fireball2.png");
        getComponent<Transform>().setTransform(x, y, 0, 0, 1.f, 1.f);
        addComponent<SpriteRenderer>("Fireball");
        addComponent<Rigidbody>(1, false, 0, 2);
        addComponent<Collider2D>(SPHERE);
    }

    ~Fireball() = default;
};