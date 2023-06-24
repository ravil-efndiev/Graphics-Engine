#include "TransformComponent.hpp"

namespace Rvl
{
    TransformComponent::TransformComponent(const glm::vec3& position, float rotationDeg, const glm::vec2& scale)
    {
        _transform = Transform(position, rotationDeg, scale);

        Position = Property<glm::vec3> 
        (
            &_transform.Position,
            GET { return _transform.Position; },
            SET { _transform.Position = value; }
        );

        Scale = Property<glm::vec2> 
        (
            &_transform.Scale,
            GET { return _transform.Scale; },
            SET { _transform.Scale = value; }
        );

        RotationZ = Property<float> 
        (
            &_transform.Rotation,
            GET { return _transform.Rotation; },
            SET { _transform.Rotation = value; }
        );
    }

    TransformComponent::operator const Transform& () const
    {
        return _transform;   
    }

}
