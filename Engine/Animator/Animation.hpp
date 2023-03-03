#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include "../ECS/Entity.h"



enum class EAnimationType {
    IDLE,
    WALK,
    RUN,
    ATTACK,
    JUMP,
    FALL,
    HIT,
    DEATH,
    NONE
};

class Animation {
public:
    Animation() {
        type = EAnimationType::NONE;
    }
    virtual ~Animation() = default;

    virtual void update(float deltaTime, Entity* entity) = 0;
    virtual void addTransition(std::shared_ptr<Animation> animation) {
        next.push_back(std::move(animation));
    }

    virtual void setParent(Animation* animation) {
        parent = animation;
    }

    virtual EAnimationType getType() {
        return type;
    }

    virtual void setActive(bool active) {
        isActive = active;
    }

    virtual bool getActive() {
        return isActive;
    }

    virtual std::vector<std::shared_ptr<Animation>> getNext() const {
        return next;
    }

protected:

    EAnimationType type = EAnimationType::NONE;
    Animation* parent = nullptr;
    std::vector<std::shared_ptr<Animation>> next;
    float time = 0.0f;
    float speed = 0.0f;
    int repeat = 0;
    int currentRepeat = 0;
    bool isActive = false;


};

