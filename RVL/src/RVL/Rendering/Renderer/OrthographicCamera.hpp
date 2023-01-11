#ifndef RVL_ORTHOGRAPHICCAMERA_HPP
#define RVL_ORTHOGRAPHICCAMERA_HPP

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace rvl
{
    class OrthographicCamera
    {
    public:
        OrthographicCamera(float left, float right, float top, float bottom);
        ~OrthographicCamera();

        void SetPosition(const glm::vec3& position);

        void SetRotationZ(float rotationZ);
        float GetRotationZ() const;

        glm::mat4 GetProjectionMatrix() const;
        glm::mat4 GetViewMatrix() const;

    private:
        void ResetMatrix();

        glm::mat4 _projectionMatrix;
        glm::mat4 _viewMatrix;

        glm::vec3 _position;
        float _rotationZ;
    };
}

#endif
