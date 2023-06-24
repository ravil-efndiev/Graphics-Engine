#include "Transform.hpp"

#include <glm/gtc/matrix_transform.hpp>

namespace Rvl
{
    Transform::Transform()
    {
        Position = glm::vec3(0.f);
        Rotation = glm::vec3(0.f);
        Scale = glm::vec2(0.f);
        Pivot = glm::vec3(0.f);
    }

    Transform::Transform(const glm::vec3& position, const glm::vec3& rotationDeg, const glm::vec2& scale)
    {
        Position = position;
        Rotation = rotationDeg;
        Scale = scale;
        Pivot = Position;
    }

    Transform::~Transform() {}

    glm::mat4 Transform::GetMatrix() const
    {
        glm::mat4 matrix (1.f);

        matrix = glm::translate(matrix, Position);
        matrix = glm::rotate(matrix, glm::radians(Rotation.x), glm::vec3(1, 0, 0));
        matrix = glm::rotate(matrix, glm::radians(Rotation.y), glm::vec3(0, 1, 0));
        matrix = glm::rotate(matrix, glm::radians(Rotation.z), glm::vec3(0, 0, 1));
        matrix = glm::scale(matrix, glm::vec3(Scale.x, Scale.y, 0));

        return matrix;
    }
}
