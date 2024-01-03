#include "PointLight.hpp"

namespace Rvl
{
    PointLight::PointLight(const glm::vec3& color, const glm::vec3& specular, float intensity, float linear, float quadratic)
    {
        RVL_ASSERT((
                color.length() <= glm::vec3(1, 1, 1).length() && 
                specular.length() <= glm::vec3(1, 1, 1).length()),
                "Point Light: colors must be in range of (0..1)");

        Intensity = intensity;
        Color = color;
        Specular = specular;
        Linear = linear;
        Quadratic = quadratic;
    }

    PointLight::PointLight(const glm::vec3& color, float intensity, float linear, float quadratic)
    {
        RVL_ASSERT((color.length() <= glm::vec3(1, 1, 1).length()),
                "Point Light: colors must be in range of (0..1)");

        Intensity = intensity;
        Color = color;
        Specular = {0.5f, 0.5f, 0.5f};
        Linear = linear;
        Quadratic = quadratic;
    }
}
