#pragma once

#include "Entity.h"
#include "SpriteRenderer.h"
#include "Rigidbody.h"
#include "Collider2D.h"
#include "../AssetManager/AssetManager.h"
#include "Explosion.h"
#include "SFML/Graphics.hpp"
#include <random>
#include <ctime>

class Fireball : public Entity
{
public:

    Fireball(std::function<void()>& callback, bool isFragmented, int damageDealt) : m_callback(callback), m_isFragmented(isFragmented), 
        m_timer(0.f), max_fragmented_entities(8), m_damageDealt(damageDealt)
    {
        AssetManager::get().loadTexture("Fireball", "assets/Dragon/fireball.png");
        getComponent<Transform>()->setTransform(0.f, 0.f, 0.f, 0.f, 0.6f, 0.6f);
        addComponent<SpriteRenderer>("Fireball");
        addComponent<Rigidbody>(1.f , false, 1.f, 1.f);
        if(isFragmented)
            addComponent<Collider2D>(SPHERE, std::string("Frag_fireball"));
        else 
            addComponent<Collider2D>(SPHERE, std::string("Fireball"));
    }

    Fireball(std::function<void()>& callback, bool isFragmented, sf::Vector2f scale, int damageDealt) : m_callback(callback), 
        m_isFragmented(isFragmented), m_timer(0.f), max_fragmented_entities(8), m_damageDealt(damageDealt)
    {
        AssetManager::get().loadTexture("Fireball", "assets/Dragon/fireball.png");
        getComponent<Transform>()->setTransform(0.f, 0.f, 0.f, 0.f, scale.x, scale.y);
        addComponent<SpriteRenderer>("Fireball");
        addComponent<Rigidbody>(1.f, false, 1.f, 1.f);
        if (isFragmented)
            addComponent<Collider2D>(SPHERE, std::string("Frag_fireball"));
        else
            addComponent<Collider2D>(SPHERE, std::string("Fireball"));
    }

    ~Fireball()
    {
        m_callback();
    };

    virtual inline void update(const float& deltaTime) override
    {
        if (m_isFragmented)
        {
            m_timer += deltaTime;
            if (m_timer >= 2.f)
            {
                explode();
                m_timer = 0.f;
                //EntityManager::getInstance()->eraseEntity(this);
            }
        }

        if (hasComponent<Explosion>())
        {
            m_timer += deltaTime;
            if (m_timer >= 0.5f)
                EntityManager::getInstance()->eraseEntity(this);
        }

        for (auto& comp : components)
        {
            comp->update(deltaTime);
        }
    }

    void fragmentation()
    {
        srand(time(NULL));
        for(int i = 0; i < max_fragmented_entities; i++)
        {
            float randX = ((static_cast<float>(rand()) / static_cast<float>(RAND_MAX)) * 1.0f) - 0.3f;
            float randY = (static_cast<float>(rand()) / static_cast<float>(RAND_MAX)) * -0.5f;
            /* calcul de direction */
            //sf::Vector2f direction = getComponent<Rigidbody>()->normal;
            sf::Vector2f direction(randX, randY);
            //sf::Vector2f direction = static_cast<sf::Vector2f>(sf::Mouse::getPosition()) - getComponent<Transform>()->position;
            //float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
            //direction /= length;
            direction *= 10.f;

            sf::Vector2f newPos(getComponent<Transform>()->position.x, getComponent<Transform>()->position.y);
            std::function<void()> callback = [] {};
            sf::Vector2f scale(0.2f, 0.2f);
            Fireball* fireball = new Fireball(callback, false, scale, 5);
            if (direction.x <= 0)
            {
                fireball->getComponent<SpriteRenderer>()->flipTextureLeft();
            }

            fireball->getComponent<SpriteRenderer>()->getSprite()->setColor(sf::Color::Blue);
            fireball->getComponent<Transform>()->moveTo(newPos);
            fireball->getComponent<Rigidbody>()->setVelocity(direction);
            EntityManager::getInstance()->addEntity(fireball);
        }
    }

    int getDamageDealt()
    {
        return m_damageDealt;
    };

    void explode()
    {
        addComponent<Explosion>();
        getComponent<Rigidbody>()->setVelocity(sf::Vector2f(0.f, 0.f));
        getComponent<Rigidbody>()->isStatic = true;
        destroy();

        // spawn fragmentaded entities
        if (m_isFragmented)
        {
            fragmentation();
        }
    }

private :
    std::function<void()> m_callback;
    float m_timer;
    bool m_isFragmented;
    uint8_t max_fragmented_entities;
    int m_damageDealt;
};