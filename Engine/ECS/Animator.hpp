#pragma once

#include "Component.h"
#include "../Animator/Animation.hpp"


class Animator: public Component
{
public:
    Animator(){
    };
    virtual ~Animator() = default;
    VectorMath<float> vecMath;

    virtual bool init() { return true;};
    virtual void draw(sf::RenderTarget* renderwindow) {};
    virtual void update(const float& deltaTime){
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
            _typeState = animationRoot->getType();
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
        if (_typeState == type) {
            return;
        }
        _typeState = type;
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


    EAnimationType _typeState = EAnimationType::NONE;
    Entity* entity = nullptr;
    std::shared_ptr<Animation> animationRoot = nullptr;
    std::shared_ptr<Animation> currentAnimation = nullptr;
};