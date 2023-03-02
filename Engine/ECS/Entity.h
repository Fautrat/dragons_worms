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
    Entity() 
    {
       addComponent<Transform>(0, 0);
    };
    virtual ~Entity() = default;

    template<typename T, typename... Args>
    inline T& addComponent(Args&&... arguments) {

        T* comp(new T(std::forward<Args>(arguments)...));
        comp->entity = this;
        //{comp} convertis comp en  unique ptr stockable
        //std::unique_ptr<Component> uptr{ comp };
        components.emplace_back(std::move(comp));

        if (comp->init()) 
        {
            compArray[getComponentTypeId<T>()] = comp;
            compBitset[getComponentTypeId<T>()] = true;
            return *comp;
        }

        return *static_cast<T*>(nullptr);
    }

    template<typename T>
    inline T* getComponent() 
    {
        auto comp = compArray.at(getComponentTypeId<T>());
        if (!hasComponent<T>())
        {
            throw std::runtime_error("Add component before getting it");
        }
        return static_cast<T*>(comp);
    }

    template<typename T>
    inline bool hasComponent() const
    {
        return compBitset[getComponentTypeId<T>()];
    }

    inline bool isActive() const 
    {
        return active;
    }

    inline void destroy() 
    {
        active = false;
    }

    inline void draw(sf::RenderTarget* renderwindow) 
    {
        for (auto& comp : components)
        {
            comp->draw(renderwindow);
        }
    }

    virtual inline void update(const float& deltaTime) 
    {
        for (auto& comp : components)
        {
            comp->update(deltaTime);
        }
    }

protected:
    bool active = false;
    ComponentArray compArray;
    ComponentBitset compBitset;
    std::vector<Component*> components;
};