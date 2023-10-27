#include "DirectionalLightComponent.hpp"

namespace Rvl
{
    DirectionalLightComponent::DirectionalLightComponent(const glm::vec3& ambient, const glm::vec3& diffuse, const glm::vec3& specular)
    {
        Ambient = ambient;
        Diffuse = diffuse;
        Specular = specular;
    }
    
    DirectionalLightComponent::DirectionalLightComponent(const glm::vec3& color)
    {
        Diffuse = color;
        Ambient = {0.2f, 0.2f, 0.2f};
        Specular = {0.5f, 0.5f, 0.5f};
    }
}