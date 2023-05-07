#ifndef RVL_ENTITY_HPP
#define RVL_ENTITY_HPP

#include <Rendering/Renderer/Transform.hpp>
#include <API/Components/Component.hpp>
#include <API/Property.hpp>

namespace rvl
{
    enum class Axis
    {
        None       = 0,
        Vertical   = 1,
        Horizontal = 2,
    };

    inline Axis operator|(Axis a, Axis b)
    {
        return static_cast<Axis>(static_cast<int>(a) | static_cast<int>(b));
    }

    inline Axis operator&(Axis a, Axis b)
    {
        return static_cast<Axis>(static_cast<int>(a) & static_cast<int>(b));
    }

    class Entity
    {
    public:
        Entity();
        Entity(const Transform& tf);
        ~Entity();

        Property<Transform> transform = {&_transform};

        void AddComponent(const Ref<Component>& component);

        virtual void Draw() = 0;

    protected:
        Transform _transform;

        std::vector<Ref<Component>> _components;
    };
}

#endif
