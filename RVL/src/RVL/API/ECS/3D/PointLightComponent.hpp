#pragma once
#include <Core/Core.hpp>

namespace Rvl
{
    // Point light's position is defined by it's position in Transform component
    struct PointLightComponent
    {
        PointLightComponent() = default;
        PointLightComponent(const glm::vec3& ambient, const glm::vec3& diffuse, const glm::vec3& specular, float linear, float quadratic);
        PointLightComponent(const glm::vec3& color, float linear, float quadratic);

        const float Constant = 1.f;

        glm::vec3 Ambient;
        glm::vec3 Diffuse;
        glm::vec3 Specular;

        float Linear;
        float Quadratic;
    };
}

