#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include "./Animation.hpp"

class IdleAnimation : public Animation {
public:
    IdleAnimation() {
        type = EAnimationType::IDLE;
    }
    ~IdleAnimation() = default;

    void update(const float& deltaTime, Entity* entity) override final {
        if (!isActive) {
            return;
        }
    }

    virtual void AddTransition(std::shared_ptr<Animation> animation) {
        next.push_back(std::move(animation));
    }

    virtual void setActive(bool active) {
        isActive = active;
    }


};

