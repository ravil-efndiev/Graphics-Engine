#include "Entity.hpp"

namespace Rvl
{
    Entity::Entity(Scene* scene, entt::entity id)
    {
        _scene = scene;
        _id = id;
    }
    
    bool Entity::operator==(const Entity& entity)
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
}
