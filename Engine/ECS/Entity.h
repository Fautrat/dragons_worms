#include "ECS.h"
#include <vector>
#include <memory>
#include "Component.h"

class Entity
{
public:
    Entity() {};
    virtual ~Entity() {};

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

private:
    ComponentArray compArray;
    ComponentBitset compBitset;
    std::vector<std::unique_ptr<Component>> components;
};