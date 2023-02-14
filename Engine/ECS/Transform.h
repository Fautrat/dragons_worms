#include "Component.h"
#include "../Utils/Vect2D.h"

class Transform : public Component
{
public:
    Transform() {}
    virtual ~Transform() {};

    bool init() override final {
        position.zero();
        scale.ones();
        rotation = 0.0f;
    }

    Vect2F position;
    Vect2F scale;
    float rotation;
};