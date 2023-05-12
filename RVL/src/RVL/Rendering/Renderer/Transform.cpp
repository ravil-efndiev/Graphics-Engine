#include "Transform.hpp"

#include <glm/gtc/matrix_transform.hpp>

namespace rvl
{
    Transform::Transform()
    {
        Position = {0.f, 0.f, 0.f};
        Rotation = 0.f;
        Scale = {0.f, 0.f};
        Pivot = glm::vec3(0.f);
    }

    Transform::Transform(const glm::vec3& position, float rotationDeg, const glm::vec2& scale)
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
        matrix = glm::rotate(matrix, glm::radians(Rotation), glm::vec3(0, 0, 1));
        matrix = glm::scale(matrix, glm::vec3(Scale.x, Scale.y, 0));

        return matrix;
    }
}
