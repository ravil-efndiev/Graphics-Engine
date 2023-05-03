#include "OrthographicCamera.hpp"
#include <Rvlpch.hpp>

namespace rvl
{

    OrthographicCamera::OrthographicCamera(const glm::vec3& position, float zoom)
    {
        _position = position;
        _viewMatrix = glm::mat4(1.0f);
        _projectionMatrix = glm::mat4(1.0f);
        _zoom = zoom;
        _rotationZ = 0;
        ResetMatrix();
    }

    OrthographicCamera::~OrthographicCamera() {}

    void OrthographicCamera::SetPosition(const glm::vec3& position)
    {
        _position = position;
        ResetMatrix();
    }

    glm::vec3 OrthographicCamera::GetPosition() const
    {
        return _position;
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

    glm::mat4 OrthographicCamera::GetProjectionMatrix(float viewportWidth, float viewportHeight)
    {
        float aspectRatio = viewportWidth / viewportHeight;
        _projectionMatrix = glm::ortho(-aspectRatio * _zoom, aspectRatio * _zoom, -_zoom, _zoom, -1.0f, 1.0f);
        return _projectionMatrix;
    }

    glm::mat4 OrthographicCamera::GetViewMatrix()
    {
        return _viewMatrix;
    }

    float OrthographicCamera::GetZoom() const
    {
        return _zoom;
    }

    void OrthographicCamera::SetZoom(float zoom)
    {
        if (zoom < 0)
            _zoom = 0;
        else
            _zoom = zoom;
    }

    void OrthographicCamera::ResetMatrix()
    {
        glm::mat4 transform = glm::translate(glm::mat4(1.0f), _position);
        transform = glm::rotate(transform, _rotationZ, glm::vec3(0, 0, 1));
        
        _viewMatrix = glm::inverse(transform);
    }
}
