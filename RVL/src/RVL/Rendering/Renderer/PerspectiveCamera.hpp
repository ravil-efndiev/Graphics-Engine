#ifndef RVL_PERSPECTIVECAMERA_HPP
#define RVL_PERSPECTIVECAMERA_HPP

#include <Rvlglpch.hpp>

namespace rvl
{
    class PerspectiveCamera
    {
    public:
        PerspectiveCamera(const glm::vec3& position, float FOV);
        ~PerspectiveCamera();

        glm::mat4 GetProjection(int width, int height);
        glm::mat4 GetView();

    private:
        glm::vec3 _position;
        float _FOV;

        glm::mat4 _projectionMatrix;
        glm::mat4 _viewMatrix;

    };
}

#endif
