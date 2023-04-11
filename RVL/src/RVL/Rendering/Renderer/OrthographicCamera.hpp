#ifndef RVL_ORTHOGRAPHICCAMERA_HPP
#define RVL_ORTHOGRAPHICCAMERA_HPP

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace rvl
{
    class OrthographicCamera
    {
    public:
        OrthographicCamera(const glm::vec3& position, int zoom = 100);
        ~OrthographicCamera();

        void SetPosition(const glm::vec3& position);

        void SetRotationZ(float rotationZ);
        float GetRotationZ() const;

        glm::mat4 GetProjectionMatrix(float viewportWidth, float viewportHeight);
        glm::mat4 GetViewMatrix();

        int GetZoom() const;
        void SetZoom(int zoom);

    private:
        void ResetMatrix();

        glm::mat4 _projectionMatrix;
        glm::mat4 _viewMatrix;

        glm::vec3 _position;
        float _rotationZ;

        int _zoom;
    };
}

#endif
