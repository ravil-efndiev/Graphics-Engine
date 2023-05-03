#include "Transform.hpp"

#include <glm/gtc/matrix_transform.hpp>

namespace rvl
{
    Transform::Transform()
    {
        Position = {0.f, 0.f, 0.f};
        Rotation = 0.f;
        Scale = {0.f, 0.f};

        _matrix = glm::translate(glm::mat4(1.f), Position) 
                * glm::rotate(glm::mat4(1.f), glm::radians(Rotation), glm::vec3(0, 0, 1))
                * glm::scale(glm::mat4(1.f), glm::vec3(Scale.x, Scale.y, 0));
    }

    Transform::Transform(const glm::vec3& position, float rotationDeg, const glm::vec2& scale)
    {
        Position = position;
        Rotation = rotationDeg;
        Scale = scale;

        _matrix = glm::translate(glm::mat4(1.f), Position) 
                * glm::rotate(glm::mat4(1.f), glm::radians(Rotation), glm::vec3(0, 0, 1))
                * glm::scale(glm::mat4(1.f), glm::vec3(Scale.x, Scale.y, 0));
    }

    Transform::~Transform() {}

    glm::mat4 Transform::GetMatrix()
    {
        _matrix = glm::translate(glm::mat4(1.f), Position) 
                * glm::rotate(glm::mat4(1.f), glm::radians(Rotation), glm::vec3(0, 0, 1))
                * glm::scale(glm::mat4(1.f), glm::vec3(Scale.x, Scale.y, 0));

        return _matrix; 
    }
}
