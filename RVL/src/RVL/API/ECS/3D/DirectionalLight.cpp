#include "DirectionalLight.hpp"

namespace Rvl
{
    DirectionalLight::DirectionalLight(const glm::vec3& direction, const glm::vec3& color, const glm::vec3& ambient, const glm::vec3& specular, float intensity)
    {
        Color = glm::normalize(color);
        Intensity = intensity;
        Ambient = glm::normalize(ambient);
        Specular = glm::normalize(specular);
        Direction = glm::normalize(direction);
    }

    DirectionalLight::DirectionalLight(const glm::vec3& direction, const glm::vec3& color, float intensity)
    {
        Color = glm::normalize(color);
        Intensity = intensity;
        Ambient = {0.2f, 0.2f, 0.2f};
        Specular = {0.5f, 0.5f, 0.5f};
        Direction = glm::normalize(direction);
    }
}
