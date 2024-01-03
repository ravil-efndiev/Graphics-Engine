#include "DirectionalLight.hpp"

namespace Rvl
{
    DirectionalLight::DirectionalLight(const glm::vec3& color, const glm::vec3& ambient, const glm::vec3& specular, float intensity)
    {
        RVL_ASSERT((ambient.length() <= glm::vec3(1, 1, 1).length() && 
                color.length() <= glm::vec3(1, 1, 1).length() && 
                specular.length() <= glm::vec3(1, 1, 1).length()),
                "colors must be in range of (0..1)");

        Color = color;
        Intensity = intensity;
        Ambient = ambient;
        Specular = specular;
    }

    DirectionalLight::DirectionalLight(const glm::vec3& color, float intensity)
    {
        RVL_ASSERT((color.length() <= glm::vec3(1, 1, 1).length()), "colors must be in range of (0..1)");

        Color = color;
        Intensity = intensity;
        Ambient = {0.2f, 0.2f, 0.2f};
        Specular = {0.5f, 0.5f, 0.5f};
    }
}
