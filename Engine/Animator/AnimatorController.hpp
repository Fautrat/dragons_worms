#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <memory>
#include "./Animation.hpp"
#include "../ECS/Entity.h"


class AnimatorController {
public:
    AnimatorController() {
    
    };
    virtual ~AnimatorController() = default;

    virtual void update(float deltaTime){
        if (!currentAnimation->getActive()) {
            getActiveAnimation();
        }
        currentAnimation->update(deltaTime, entity);
    }
    void setEntity(Entity* entity) {
        this->entity = entity;
    }

    void AddAnimation(std::shared_ptr<Animation> animation) {
        if (animationRoot == nullptr) {
            animationRoot = std::move(animation);
            currentAnimation = animationRoot;
            _type = animationRoot->getType();
        }
        else {
            animationRoot->addTransition(animation);
        }
    }

    void getActiveAnimation() {
        for (auto& animation : currentAnimation->getNext()) {
            if (animation->getActive()) {
                currentAnimation = animation;
                break;
            }
        }
    }

    void setAnimation(EAnimationType type) {
        if (_type == type) {
            return;
        }
        _type = type;
        currentAnimation->setActive(false);
        currentAnimation = animationRoot;
        for (auto& animation : currentAnimation->getNext()) {
            if (animation->getType() == type) {
                currentAnimation = animation;
                break;
            }
        }
        currentAnimation->setActive(true);
    }


    EAnimationType _type = EAnimationType::NONE;
    Entity* entity = nullptr;
    std::shared_ptr<Animation> animationRoot = nullptr;
    std::shared_ptr<Animation> currentAnimation = nullptr;
};

