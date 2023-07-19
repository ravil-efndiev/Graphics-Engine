#include "TransformComponent.hpp"

namespace Rvl
{
    TransformComponent::TransformComponent(const glm::vec3& position, const glm::vec3& rotationDeg, const glm::vec3& scale)
    {
        _transform = Transform(position, rotationDeg, scale);

        Position = Property<glm::vec3> 
        (
            &_transform.Position,
            GET { return _transform.Position; },
            SET { _transform.Position = value; }
        );

        Rotation = Property<glm::vec3> 
        (
            &_transform.Rotation,
            GET { return _transform.Rotation; },
            SET { _transform.Rotation = value; }
        );

        Scale = Property<glm::vec3> 
        (
            &_transform.Scale,
            GET { return _transform.Scale; },
            SET { _transform.Scale = value; }
        );
    }

    TransformComponent::operator const Transform& () const
    {
        return _transform;   
    }

}
