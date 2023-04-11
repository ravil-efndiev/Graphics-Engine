#ifndef RVL_PERSPECTIVECAMERA_HPP
#define RVL_PERSPECTIVECAMERA_HPP

#include <Rvlglpch.hpp>

#define MOVE_FORWARD 0
#define MOVE_BACKWARD 1
#define MOVE_RIGHT 2
#define MOVE_LEFT 3

namespace rvl
{
    class PerspectiveCamera
    {
    public:
        typedef unsigned short direction_t;
        
        glm::vec3 Position;

        PerspectiveCamera(const glm::vec3& position, float FOV);
        ~PerspectiveCamera();

        void Rotate(float x, float y, float z);
        void ResetRotation();

        glm::mat4 GetProjectionMatrix(float viewportWidth, float viewportHeight) const;
        glm::mat4 GetViewMatrix() const;

        void Move(direction_t direction, float speed, const float& deltaTime);

    private:
        float _FOV;

        glm::vec3 _forward, _up, _right;
        glm::mat4 _rotation;

        void ResetVectors();
    };
}

#endif
