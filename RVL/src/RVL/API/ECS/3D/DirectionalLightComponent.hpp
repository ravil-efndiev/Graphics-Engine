#pragma once
#include <Core/Core.hpp>

namespace Rvl
{
    // Directional light's direction is defined by it's rotation in Transform component
    struct DirectionalLightComponent
    {
        DirectionalLightComponent() = default;
        DirectionalLightComponent(const glm::vec3& ambient, const glm::vec3& diffuse, const glm::vec3& specular);
        DirectionalLightComponent(const glm::vec3& color);

        glm::vec3 Ambient;
        glm::vec3 Diffuse;
        glm::vec3 Specular;
    };
}

