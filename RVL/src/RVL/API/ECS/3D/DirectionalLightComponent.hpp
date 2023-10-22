#pragma once
#include <Core/Core.hpp>

namespace Rvl
{
    // Directional light's direction is defined by it's rotation in Transform component
    class DirectionalLightComponent
    {
    public:
        DirectionalLightComponent(const glm::vec3& ambient, const glm::vec3& diffuse, const glm::vec3& specular);

        void SetAmbient(const glm::vec3& ambient);
        void SetDiffuse(const glm::vec3& diffuse);
        void SetSpecular(const glm::vec3& specular);

        glm::vec3 GetAmbient() const;
        glm::vec3 GetDiffuse() const;
        glm::vec3 GetSpecular() const;

    private:
        glm::vec3 _ambient;
        glm::vec3 _diffuse;
        glm::vec3 _specular;
    };
}

