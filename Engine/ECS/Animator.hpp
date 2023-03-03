#pragma once

#include "Component.h"
#include "../Animator/AnimatorController.hpp"


class Animator: public Component
{
public:
    Animator(){
        _animatorController = new AnimatorController();
    }
    Animator(AnimatorController* animatorController) : _animatorController(animatorController) {
        _animatorController->setEntity(entity);
    };
    virtual ~Animator() = default;
    Entity* entity;
    VectorMath<float> vecMath;

    virtual bool init() { return true;};
    virtual void draw(sf::RenderTarget* renderwindow) {};
    virtual void update(const float& deltaTime) {
        _animatorController->update(deltaTime);
    };

    void AddAnimation(std::shared_ptr<Animation> animation) {
        _animatorController->AddAnimation(animation);
    }

    void setEntity(Entity* entity) {
        _animatorController->setEntity(entity);
    }

    void setAnimation(EAnimationType type) {
        _animatorController->setAnimation(type);
    }

private:
    AnimatorController* _animatorController;
};