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

    void update(float deltaTime, Entity* entity) override final {
        std::cout << "IdleAnimation" << std::endl;
        if (!isActive) {
            return;
        }
    }

    virtual void AddTransition(std::shared_ptr<Animation> animation) {
        next.push_back(std::move(animation));
    }


};

