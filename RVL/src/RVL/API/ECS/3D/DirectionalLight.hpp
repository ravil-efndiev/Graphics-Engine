#pragma once
#include <Core/Core.hpp>

namespace Rvl
{
    // Directional light's direction is defined by it's rotation in Transform component
    struct DirectionalLight
    {
        DirectionalLight() = default;
        DirectionalLight(const glm::vec3& color, const glm::vec3& ambient, const glm::vec3& specular, float intensity = 1);
        DirectionalLight(const glm::vec3& color, float intensity = 1);

        glm::vec3 Ambient;
        glm::vec3 Specular;
        glm::vec3 Color;
        float Intensity;
    };
}

