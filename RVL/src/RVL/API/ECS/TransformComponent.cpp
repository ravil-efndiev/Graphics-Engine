#include "TransformComponent.hpp"

namespace Rvl
{
    TransformComponent::TransformComponent(const glm::vec3& position, float rotationDeg, const glm::vec2& scale)
    {
        _transform = Transform(position, rotationDeg, scale);

        Position = Property<glm::vec3> (
            &_transform.Position,
            [this]() -> glm::vec3 { return _transform.Position; },
            [this](const auto& value) { _transform.Position = value; }
        );

        Scale = Property<glm::vec2> (
            &_transform.Scale,
            [this]() -> glm::vec2 { return _transform.Scale; },
            [this](const auto& value) { _transform.Scale = value; }
        );

        RotationZ = Property<float> (
            &_transform.Rotation,
            [this]() -> float { return _transform.Rotation; },
            [this](const auto& value) { _transform.Rotation = value; }
        );
    }

    TransformComponent::operator const Transform& () const
    {
        return _transform;   
    }

}
