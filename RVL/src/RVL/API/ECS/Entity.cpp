#include "Entity.hpp"

namespace Rvl
{
    Entity::Entity(Scene* scene, entt::entity id)
    {
        _scene = scene;
        _id = id;
    }
}
