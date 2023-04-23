#include "Entity.hpp"
#include <iostream>

namespace rvl
{
    Entity::Entity()
    {
        _position = Vector2f::Zero();

        _position.SetOnChangeCallback(
            [this]()
            {
                ResetPosition();
            }
        );
    }

    Entity::Entity(float x, float y)
    {
        _position = {x, y};

        _position.SetOnChangeCallback(
            [this]()
            {
                ResetPosition();
            }
        );
    }

    Entity::Entity(const Vector2f &position) : _position(position) {}

    Entity::~Entity() {}
    
    void Entity::ResetPosition()
    {
    }
}
