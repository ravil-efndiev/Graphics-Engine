#include "PerspectiveCamera.hpp"
#include <Core/Core.hpp>

namespace rvl
{
    
    PerspectiveCamera::PerspectiveCamera(const glm::vec3& position, float FOV)
    {
        Position = position;
        _FOV = FOV;

        _rotation = glm::mat4(1.0f);

        ResetVectors();
    }

    PerspectiveCamera::~PerspectiveCamera()
    {
    }

    void PerspectiveCamera::ResetVectors()
    {
        _forward = glm::vec3(_rotation * glm::vec4(0, 0, -1, 1));
        _right   = glm::vec3(_rotation * glm::vec4(-1, 0, 0, 1));
        _up      = glm::vec3(_rotation * glm::vec4(0, 1, 0, 1));
    }

    void PerspectiveCamera::Rotate(float x, float y, float z)
    {
        _rotation = glm::rotate(_rotation, z, glm::vec3(0, 0, 1));
        _rotation = glm::rotate(_rotation, y, glm::vec3(0, 1, 0));
        _rotation = glm::rotate(_rotation, x, glm::vec3(1, 0, 0));

        ResetVectors();
    }

    void PerspectiveCamera::ResetRotation()
    {
        _rotation = glm::mat4(1.f);
    }

    glm::mat4 PerspectiveCamera::GetProjectionMatrix(float viewportWidth, float viewportHeight) const
    {
        float aspect = viewportWidth / viewportHeight;
        return glm::perspective(70.f, aspect, 0.1f, 100.f);
    }

    glm::mat4 PerspectiveCamera::GetViewMatrix() const
    {
        return glm::lookAt(Position, Position + _forward, _up);
    }

    void PerspectiveCamera::Move(direction_t direction, float speed, const float &deltaTime)
    {
        switch (direction)
        {
            case MOVE_FORWARD:
                Position += _forward * speed * deltaTime;
                break;
            case MOVE_BACKWARD:
                Position -= _forward * speed * deltaTime;
                break;
            case MOVE_RIGHT:
                Position += _right * speed * deltaTime;
                break;   
            case MOVE_LEFT:
                Position -= _right * speed * deltaTime;
                break;
            default:
                throw Error("Invalid camera movement direction", RVL_INTERNAL_ERROR);
        }
    }
}
