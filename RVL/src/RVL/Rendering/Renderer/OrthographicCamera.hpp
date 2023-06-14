#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace Rvl
{
    class OrthographicCamera
    {
    public:
        OrthographicCamera(const glm::vec3& position, float zoom = 1.f);
        ~OrthographicCamera();

        void SetPosition(const glm::vec3& position);
        glm::vec3 GetPosition() const;

        void SetRotationZ(float rotationZ);
        float GetRotationZ() const;

        glm::mat4 GetProjectionMatrix(float viewportWidth, float viewportHeight);
        glm::mat4 GetViewMatrix();

        float GetZoom() const;
        void SetZoom(float zoom);

    private:
        void ResetMatrix();

        glm::mat4 _projectionMatrix;
        glm::mat4 _viewMatrix;

        glm::vec3 _position;
        float _rotationZ;

        float _zoom;
    };
}

