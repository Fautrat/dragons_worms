#pragma once

#include <SFML/Graphics.hpp>
#include "../ECS/Entity.h"
#include "Animation.hpp"
#include "IdleAnimation.hpp"



class HitAnimation : public Animation {
public:
    HitAnimation() : Animation(),  duration(0.5f), repeat(5), isRed(false) {
        type = EAnimationType::HIT;

        parent = std::make_shared<IdleAnimation>();
    }
    virtual ~HitAnimation() = default;

    virtual void update(float deltaTime, Entity* entity) override final{

        time += deltaTime;
        if (time > duration/2.f) {
            time = 0.f;
            if (repeat > 0) {
                if(isRed) {
                    repeat--;
                    entity->getComponent<SpriteRenderer>()->getSprite()->setColor(sf::Color(255, 255, 255));
                }
                else {
//                    entity->getComponent<SpriteRenderer>()->getSprite()
                    entity->getComponent<SpriteRenderer>()->getSprite()->setColor(sf::Color(255, 0, 0));
                }
                isRed = !isRed;
            }
            else {
                entity->getComponent<SpriteRenderer>()->getSprite()->setColor(sf::Color(255, 255, 255));
                parent->setActive(true);
                setActive(false);
            }
        }
    }

protected:


private:
    float time = 0.f;
    float duration;
    int repeat;
    bool isRed = false;
    std::shared_ptr<IdleAnimation> parent = nullptr;
    bool isActive = false;
    sf::Sprite* savedSprite = nullptr;


};

