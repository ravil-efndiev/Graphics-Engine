#include "PointLightComponent.hpp"

namespace Rvl
{
    PointLightComponent::PointLightComponent(const glm::vec3& ambient, const glm::vec3& diffuse, const glm::vec3& specular, float linear, float quadratic)
    {
        _ambient = ambient;
        _diffuse = diffuse;
        _specular = specular;
        _linear = linear;
        _quadratic = quadratic;
    }

    void PointLightComponent::SetAmbient(const glm::vec3& ambient) 
    {
        _ambient = ambient;
    }
    void PointLightComponent::SetDiffuse(const glm::vec3& diffuse) 
    {
        _diffuse = diffuse;
    }
    void PointLightComponent::SetSpecular(const glm::vec3& specular) 
    {
        _specular = specular;
    }

    void PointLightComponent::SetLinear(float linear)
    {
        _linear = linear;
    }
    void PointLightComponent::SetQuadratic(float quadratic)
    {
        _quadratic = quadratic;
    }

    glm::vec3 PointLightComponent::GetAmbient() const 
    {
        return _ambient;
    }
    glm::vec3 PointLightComponent::GetDiffuse() const 
    {
        return _diffuse;
    }
    glm::vec3 PointLightComponent::GetSpecular() const 
    {
        return _specular;
    }
    float PointLightComponent::GetLinear() const
    {
        return _linear;
    }
    float PointLightComponent::GetQuadratic() const
    {
        return _quadratic;
    }
}
