#pragma once

#include <Core/Core.hpp>

namespace Rvl
{
    class Entity;
    class Transform
    {
    public:
        Transform();
        Transform(const glm::vec3& position, const glm::vec3& rotationDeg, const glm::vec3& scale);
        ~Transform();

        bool operator== (const Transform& other) const;
        bool operator!= (const Transform& other) const;

        glm::mat4 GetMatrix() const;

        glm::vec3 Position;
        glm::vec3 Rotation;
        glm::vec3 Scale;

        glm::vec3 Pivot;

        friend void TransformSystem(const std::vector<Entity>&);
    private:
        glm::mat4 _parentMatrix {1.f};
    };
}
