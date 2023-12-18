#include "PointLight.hpp"

namespace Rvl
{
    PointLight::PointLight(const glm::vec3& ambient, const glm::vec3& diffuse, const glm::vec3& specular, float linear, float quadratic, float intensity)
    {
        RVL_ASSERT((ambient.length() <= glm::vec3(1, 1, 1).length() && 
                diffuse.length() <= glm::vec3(1, 1, 1).length() && 
                specular.length() <= glm::vec3(1, 1, 1).length()),
                "colors must be in range of (0..1)");

        Intensity = intensity;
        Color = diffuse;
        Diffuse = Color * Intensity;
        Ambient = ambient;
        Specular = specular;
        Linear = linear;
        Quadratic = quadratic;
    }

    PointLight::PointLight(const glm::vec3& color, float linear, float quadratic, float intensity)
    {
        RVL_ASSERT((color.length() <= glm::vec3(1, 1, 1).length()),
                "colors must be in range of (0..1)");

        Intensity = intensity;
        Color = color;
        Diffuse = Color * Intensity;
        Ambient = {0.2f, 0.2f, 0.2f};
        Specular = {0.5f, 0.5f, 0.5f};
        Linear = linear;
        Quadratic = quadratic;
    }
}
