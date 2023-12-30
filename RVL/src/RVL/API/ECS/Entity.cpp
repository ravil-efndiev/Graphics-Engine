#include "Entity.hpp"

namespace Rvl
{
    Entity::Entity(Scene* scene, entt::entity id)
    {
        _scene = scene;
        _id = id;
    }
    
    bool Entity::operator==(const Entity& entity) const
    {
        return _id == entity._id && _scene == entity._scene;
    }

    entt::entity Entity::GetId() const
    {
        return _id;
    }
    
    uint32 Entity::GetIdInt() const
    {
        return (uint32)_id;
    }

    void Entity::AddChild(Entity child)
    {
        _scene->AddChild(*this, child);
    }

    void Entity::RemoveChild(Entity child)
    {
        _scene->RemoveChild(*this, child);
    }

    Entity Entity::Instantiate()
    {
        return _scene->Instantiate(*this);
    }

    EntityData& Entity::GetData()
    {
        return _scene->GetEntityData(*this);
    }


}
