#pragma once

#include "Camera.hpp"
#include <glm/gtc/type_ptr.hpp>

namespace Rvl
{
    class PerspectiveCamera : public Camera
    {
    public:
        PerspectiveCamera(const glm::vec3& position, float FOV);
        ~PerspectiveCamera();

        void Rotate(float x, float y, float z);
        void ResetRotation();

        void SetPosition(const glm::vec3& pos);
        glm::vec3 GetPosition() const;

        glm::mat4 GetProjectionMatrix(float viewportWidth, float viewportHeight) const override;
        glm::mat4 GetViewMatrix() const override;

        friend class UserPerspectiveCamera;

    private:
        float _FOV;

        glm::vec3 _forward, _up, _right;
        glm::mat4 _rotation;

        glm::vec3 _position;

        glm::vec3 _vecRotation;

        void ResetVectors();
    };
}

