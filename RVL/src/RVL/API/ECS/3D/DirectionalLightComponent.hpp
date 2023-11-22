#pragma once
#include <Core/Core.hpp>

namespace Rvl
{
    // Directional light's direction is defined by it's rotation in Transform component
    struct DirectionalLightComponent
    {
        DirectionalLightComponent() = default;
        DirectionalLightComponent(const glm::vec3& ambient, const glm::vec3& diffuse, const glm::vec3& specular, float intensity = 1);
        DirectionalLightComponent(const glm::vec3& color, float intensity = 1);

        glm::vec3 Ambient;
        glm::vec3 Diffuse;
        glm::vec3 Specular;
        glm::vec3 Color;
        float Intensity;
    };
}

