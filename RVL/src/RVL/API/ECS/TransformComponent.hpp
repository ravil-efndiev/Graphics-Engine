#ifndef RVL_TRANSFORMCOMPONENT_HPP
#define RVL_TRANSFORMCOMPONENT_HPP

#include <Rendering/Renderer/Transform.hpp>
#include <API/Property.hpp>

namespace Rvl
{
    class TransformComponent
    {
    public:
        TransformComponent() = default;
        TransformComponent(const TransformComponent&) = default;
        TransformComponent(const glm::vec3& position, float rotationDeg, const glm::vec2& scale);

        Property<glm::vec3> Position;
        Property<glm::vec2> Scale;
        Property<float> RotationZ;

        operator const Transform& () const;

    private:
        Transform _transform;
    };
}

#endif
