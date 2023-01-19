#include "PerspectiveCamera.hpp"

namespace rvl
{
    PerspectiveCamera::PerspectiveCamera(const glm::vec3 &position, float FOV)
    {
        _position = position;
        _FOV = FOV;
    }

    PerspectiveCamera::~PerspectiveCamera() {}

    glm::mat4 PerspectiveCamera::GetProjection(int width, int height)
    {
        return glm::mat4(1);
    }
    
    glm::mat4 PerspectiveCamera::GetView()
    {
        return glm::mat4();
    }
}
