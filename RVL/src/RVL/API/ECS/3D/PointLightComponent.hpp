#pragma once
#include <Core/Core.hpp>

namespace Rvl
{
    // Point light's position is defined by it's position in Transform component
    class PointLightComponent
    {
    public:
        PointLightComponent(const glm::vec3& ambient, const glm::vec3& diffuse, const glm::vec3& specular, float linear, float quadratic);

        const float Constant = 1.f;

        void SetAmbient(const glm::vec3& ambient);
        void SetDiffuse(const glm::vec3& diffuse);
        void SetSpecular(const glm::vec3& specular);
        void SetLinear(float linear);
        void SetQuadratic(float quadratic);

        glm::vec3 GetAmbient() const;
        glm::vec3 GetDiffuse() const;
        glm::vec3 GetSpecular() const;
        float GetLinear() const;
        float GetQuadratic() const;

    private:
        glm::vec3 _ambient;
        glm::vec3 _diffuse;
        glm::vec3 _specular;

        float _linear;
        float _quadratic;
    };
}

