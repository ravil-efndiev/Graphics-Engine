#include "DirectionalLightComponent.hpp"

namespace Rvl
{
    DirectionalLightComponent::DirectionalLightComponent(const glm::vec3& ambient, const glm::vec3& diffuse, const glm::vec3& specular)
    {
        _ambient = ambient;
        _diffuse = diffuse;
        _specular = specular;
    }

    void DirectionalLightComponent::SetAmbient(const glm::vec3& ambient) 
    {
        _ambient = ambient;
    }
    void DirectionalLightComponent::SetDiffuse(const glm::vec3& diffuse) 
    {
        _diffuse = diffuse;
    }
    void DirectionalLightComponent::SetSpecular(const glm::vec3& specular) 
    {
        _specular = specular;
    }

    glm::vec3 DirectionalLightComponent::GetAmbient() const 
    {
        return _ambient;
    }
    glm::vec3 DirectionalLightComponent::GetDiffuse() const 
    {
        return _diffuse;
    }
    glm::vec3 DirectionalLightComponent::GetSpecular() const 
    {
        return _specular;
    }
}