#ifndef RVL_ENTITY_HPP
#define RVL_ENTITY_HPP

#include <Rendering/Renderer/Transform.hpp>
#include <API/Components/Component.hpp>
#include <API/Property.hpp>

namespace rvl
{
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
