#include <array>
#include <bitset>

class Entity;
class Component;

using ComponentTypeID = std::size_t;

inline ComponentTypeID getUniqueComponentID()
{
    static ComponentTypeID lastID = 0;
    return lastID++;
}

template<typename T>
inline ComponentTypeID getComponentTypeId() noexcept
{
    static_assert(std::is_base_of<Component, T>::value, "Type not base on Component !");
    static const ComponentTypeID typeID = getUniqueComponentID();
    return typeID;
}

// A revoir combien de max on a besoin
constexpr std::size_t MAX_ENTITIES = 1000;
constexpr std::size_t MAX_COMPONENTS = 32;

using ComponentBitset = std::bitset<MAX_COMPONENTS>;
using ComponentArray = std::array<Component*, MAX_COMPONENTS>;
