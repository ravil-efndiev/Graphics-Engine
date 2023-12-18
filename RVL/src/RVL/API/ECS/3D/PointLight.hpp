#pragma once
#include <Core/Core.hpp>

namespace Rvl
{
    // Point light's position is defined by it's position in Transform component
    struct PointLight
    {
        PointLight() = default;
        PointLight(const glm::vec3& ambient, const glm::vec3& diffuse, const glm::vec3& specular, float linear, float quadratic, float intensity = 1);
        PointLight(const glm::vec3& color, float linear, float quadratic, float intensity = 1);

        const float Constant = 1.f;

        glm::vec3 Color;
        glm::vec3 Ambient;
        glm::vec3 Diffuse;
        glm::vec3 Specular;

        float Intensity;
        float Linear;
        float Quadratic;
    };
}

