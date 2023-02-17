#pragma once

#include "ECS.h"
#include <vector>
#include <memory>
#include "Component.h"
#include "Transform.h"
#include "SFML/Graphics.hpp"

class Entity
{
public:
    Entity() {
        this->addComponent<Transform>(0, 0);
    };
    virtual ~Entity() = default;

    template<typename T, typename... Args>
    inline T& addComponent(Args&&... arguments) {

        T* comp(new T(std::forward<Args>(arguments)...));

        //{comp} convertis comp en  unique ptr stockable
        std::unique_ptr<Component> uptr{ comp };
        components.emplace_back(std::move(uptr));

        if (comp->init()) {
            compArray[getComponentTypeId<T>()] = comp;
            compBitset[getComponentTypeId<T>()] = true;
            comp->entity = this;
            return *comp;
        }

        return *static_cast<T*>(nullptr);
    }

    template<typename T>
    inline T& getComponent() const {
        auto ptr(compArray[getComponentTypeId<T>()]);
        return *static_cast<T*>(ptr);
    }

    template<typename T>
    inline bool hasComponent() const
    {
        return compBitset[getComponentTypeId<T>()];
    }

    inline bool isActive() const {
        return active;
    }

    inline void destroy() {
        active = false;
    }

    inline void draw(sf::RenderTarget* renderwindow) {
        for (auto& comp : components)
        {
            comp->draw(renderwindow);
        }
    }

    inline void update() {
        for (auto& comp : components)
        {
            comp->update();
        }
    }


private:
    bool active = false;
    ComponentArray compArray;
    ComponentBitset compBitset;
    std::vector<std::unique_ptr<Component>> components;
};