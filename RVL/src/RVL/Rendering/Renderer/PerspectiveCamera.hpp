#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace Rvl
{
    class PerspectiveCamera
    {
    public:
        glm::vec3 Position;

        PerspectiveCamera(const glm::vec3& position, float FOV);
        ~PerspectiveCamera();

        void Rotate(float x, float y, float z);
        void ResetRotation();

        glm::mat4 GetProjectionMatrix(float viewportWidth, float viewportHeight) const;
        glm::mat4 GetViewMatrix() const;

    private:
        float _FOV;

        glm::vec3 _forward, _up, _right;
        glm::mat4 _rotation;

        void ResetVectors();
    };
}

