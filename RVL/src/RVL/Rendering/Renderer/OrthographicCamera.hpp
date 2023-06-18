#pragma once

#include "Camera.hpp"
#include <glm/gtc/matrix_transform.hpp>

namespace Rvl
{
    class OrthographicCamera : public Camera
    {
    public:
        OrthographicCamera(const glm::vec3& position, float zoom = 1.f);
        ~OrthographicCamera();

        void SetPosition(const glm::vec3& position);
        glm::vec3 GetPosition() const;

        void SetRotationZ(float rotationZ);
        float GetRotationZ() const;

        glm::mat4 GetProjectionMatrix(float viewportWidth, float viewportHeight) const override;
        glm::mat4 GetViewMatrix() const override;

        float GetZoom() const;
        void SetZoom(float zoom);

    private:
        void ResetMatrix();

        glm::mat4 _viewMatrix;

        glm::vec3 _position;
        float _rotationZ;

        float _zoom;
    };
}

