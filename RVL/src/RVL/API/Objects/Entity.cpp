#include "Entity.hpp"

namespace rvl
{

    Entity::Entity(const Transform& tf)
    {
        _transform = tf;
    }

    Entity::Entity() : Entity({{0.f, 0.f, 0.f}, 0.f, {1.f, 1.f}}) {}

    Entity::~Entity() {}
    
    void Entity::AddComponent(const Ref<Component>& component)
    {
        _components.push_back(component);
        component->OnAttach();
    }


}
