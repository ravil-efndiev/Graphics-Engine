#pragma once
#include <Core/Core.hpp>

namespace Rvl
{
    // Point light's position is defined by it's position in Transform component
    struct PointLight
    {
        PointLight() = default;
        PointLight(const glm::vec3& color, const glm::vec3& specular, float intensity = 1, float linear = 0.9f, float quadratic = 0.32f);
        PointLight(const glm::vec3& color, float intensity = 1, float linear = 0.9f, float quadratic = 0.32f);

        const float Constant = 1.f;

        glm::vec3 Color;
        glm::vec3 Specular;

        float Intensity;
        float Linear;
        float Quadratic;
    };
}

