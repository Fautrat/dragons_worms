#pragma once

#include <SFML/Graphics.hpp>
#include "../ECS/Entity.h"
#include "Animation.hpp"
#include "IdleAnimation.hpp"



class HitAnimation : public Animation {
public:
    HitAnimation() : Animation(),  duration(0.5f), repeat(3), isRed(false) {
        type = EAnimationType::HIT;

        parent = std::make_shared<IdleAnimation>();
    }
    virtual ~HitAnimation() = default;

    virtual void update(const float& deltaTime, Entity* entity) override final{

        time += deltaTime;
    }

    virtual void setActive(bool active) override final {
        if (active){
            repeat = 3;
        }
        isActive = active;
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

