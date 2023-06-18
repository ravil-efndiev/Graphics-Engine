#pragma once

#include <Rendering/Renderer/Transform.hpp>
#include <API/Property.hpp>
#include "Component.hpp"

namespace Rvl
{
    class TransformComponent : public Component
    {
    public:
        TransformComponent() = default;
        TransformComponent(const TransformComponent&) = default;
        TransformComponent(const glm::vec3& position, float rotationDeg, const glm::vec2& scale);

        Property<glm::vec3> Position;
        Property<glm::vec2> Scale;
        Property<float>     RotationZ;

        operator const Transform& () const;

    private:
        Transform _transform;
    };
}
