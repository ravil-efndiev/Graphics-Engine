#include "PerspectiveCamera.hpp"
#include <Core/Core.hpp>

namespace Rvl
{
    
    PerspectiveCamera::PerspectiveCamera(const glm::vec3& position, float FOV)
    {
        _position = position;
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

        _vecRotation.x = glm::atan(_rotation[2][1], _rotation[2][2]);
        _vecRotation.y = glm::atan(-_rotation[2][0], glm::sqrt(_rotation[2][1] * _rotation[2][1] + _rotation[2][2] * _rotation[2][2]));
        _vecRotation.z = glm::atan(_rotation[1][0], _rotation[0][0]);

        ResetVectors();
    }

    void PerspectiveCamera::ResetRotation()
    {
        _rotation = glm::mat4(1.f);
    }

    void PerspectiveCamera::SetPosition(const glm::vec3& pos)
    {
        _position = pos;
    }

    glm::vec3 PerspectiveCamera::GetPosition() const
    {
        return _position;
    }

    glm::mat4 PerspectiveCamera::GetProjectionMatrix(float viewportWidth, float viewportHeight) const
    {
        float aspect = viewportWidth / viewportHeight;
        return glm::perspective(70.f, aspect, 0.1f, 100.f);
    }

    glm::mat4 PerspectiveCamera::GetViewMatrix() const
    {
        return glm::lookAt(_position, _position + _forward, _up);
    }

}
