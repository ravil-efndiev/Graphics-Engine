#pragma once

#include <glm/glm.hpp>

namespace Rvl
{
    class Transform
    {
    public:
        Transform();
        Transform(const glm::vec3& position, const glm::vec3& rotationDeg, const glm::vec2& scale);
        ~Transform();

        glm::mat4 GetMatrix() const;

        glm::vec3 Position;
        glm::vec3 Rotation;
        glm::vec2 Scale;

        glm::vec3 Pivot;
    };
}

