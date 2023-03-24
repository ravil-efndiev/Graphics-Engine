#include "Entity.hpp"

namespace rvl
{
    Entity::Entity()
    {
        _position = Vector2f::Zero();
    }

    Entity::Entity(float x, float y)
    {
        _position = {x, y};
    }

    Entity::Entity(const Vector2f &position)
    {
        _position = position;
    }

    Entity::~Entity() {}

    Vector2f& Entity::Position()
    {
        return _position;
    }
}
