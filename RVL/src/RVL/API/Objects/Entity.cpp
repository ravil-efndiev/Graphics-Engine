#include "Entity.hpp"

namespace rvl
{

    Entity::Entity(const Transform& tf)
    {
        _realPosition = {0.f, 0.f, 0.f};
        _transform = tf;
    }

    Entity::Entity() : Entity({{0.f, 0.f, 0.f}, 0.f, {1.f, 1.f}}) {}

    Entity::~Entity() {}
    
    void Entity::AddComponent(const Ref<Component>& component)
    {
        _components.push_back(component);
        component->OnAttach();
    }

    void Entity::AddChild(const Ref<Entity>& entity)
    {
        _children.push_back(entity);
        entity->_hasParent = true;
        _hasChildren = true;
    }

    void Entity::UpdateChildren()
    {
        for (auto& child : _children)
        {   
            child->_realPosition = (_hasParent ? _realPosition : _transform.Position) + child->transform->Position;
            child->_realRotationZ = (_hasParent ? _realRotationZ : _transform.Rotation) + child->transform->Rotation;

            if (child->_hasChildren) child->UpdateChildren();
        }
    }

}
