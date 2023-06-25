#pragma once

#include <Rendering/Renderer/Transform.hpp>
#include <API/Property.hpp>

namespace Rvl
{
    class TransformComponent
    {
    public:
        TransformComponent() = default;
        TransformComponent(const TransformComponent&) = default;
        TransformComponent(const glm::vec3& position, const glm::vec3& rotationDeg, const glm::vec2& scale);

        Property<glm::vec3> Position;
        Property<glm::vec3> Rotation;
        Property<glm::vec2> Scale;

        operator const Transform& () const;

    private:
        Transform _transform;
    };
}
