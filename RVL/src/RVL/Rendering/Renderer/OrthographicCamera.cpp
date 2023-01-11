#include "OrthographicCamera.hpp"

namespace rvl
{

    OrthographicCamera::OrthographicCamera(float left, float right, float top, float bottom)
    {
        _viewMatrix = glm::mat4(1.0f);
        _projectionMatrix = glm::ortho(left, right, bottom, top, -1.0f, 1.0f);
    }

    OrthographicCamera::~OrthographicCamera() {}

    void OrthographicCamera::SetPosition(const glm::vec3& position)
    {
        _position = position;
        ResetMatrix();
    }

    void OrthographicCamera::SetRotationZ(float rotationZ)
    {
        _rotationZ = rotationZ;
        ResetMatrix();
    }

    float OrthographicCamera::GetRotationZ() const
    {
        return _rotationZ;
    }

    glm::mat4 OrthographicCamera::GetProjectionMatrix() const
    {
        return _projectionMatrix;
    }

    glm::mat4 OrthographicCamera::GetViewMatrix() const
    {
        return _viewMatrix;
    }

    void OrthographicCamera::ResetMatrix()
    {
        glm::mat4 transform = glm::translate(glm::mat4(1.0f), _position);
        transform = glm::rotate(transform, _rotationZ, glm::vec3(0, 0, 1));
        
        _viewMatrix = glm::inverse(transform);
    }
}
