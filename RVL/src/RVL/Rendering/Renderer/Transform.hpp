#ifndef RVL_TRANSFORM_HPP
#define RVL_TRANSFORM_HPP

#include <glm/glm.hpp>

namespace Rvl
{
    class Transform
    {
    public:
        Transform();
        Transform(const glm::vec3& position, float rotationDeg, const glm::vec2& scale);
        ~Transform();

        glm::mat4 GetMatrix() const;

        glm::vec3 Position;
        glm::vec2 Scale;
        float Rotation;

        glm::vec3 Pivot;
    private:
    };
}

#endif
