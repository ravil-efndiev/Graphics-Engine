#include "PointLightComponent.hpp"

namespace Rvl
{
    PointLightComponent::PointLightComponent(const glm::vec3& ambient, const glm::vec3& diffuse, const glm::vec3& specular, float linear, float quadratic)
    {
        Ambient = ambient;
        Diffuse = diffuse;
        Specular = specular;
        Linear = linear;
        Quadratic = quadratic;
    }

    PointLightComponent::PointLightComponent(const glm::vec3& color, float linear, float quadratic)
    {
        Diffuse = color;
        Ambient = {0.2f, 0.2f, 0.2f};
        Specular = {0.5f, 0.5f, 0.5f};
        Linear = linear;
        Quadratic = quadratic;
    }
}
