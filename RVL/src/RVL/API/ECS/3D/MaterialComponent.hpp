#pragma once
#include <Rendering/Renderer/Material.hpp>

namespace Rvl
{
    class GLShaderProgram;
    struct MaterialComponent
    {
        MaterialComponent() = default;
        MaterialComponent(const Ref<GLShaderProgram>& shader, glm::vec3 ambient, float shininess, glm::vec3 diffuse = glm::vec3(1.f), glm::vec3 specular = glm::vec3(0.5f));
        MaterialComponent(glm::vec3 ambient, float shininess, glm::vec3 diffuse = glm::vec3(1.f), glm::vec3 specular = glm::vec3(0.5f));
        ~MaterialComponent() {}

        Ref<GLShaderProgram> GetShader() const;
        void SetShader(const Ref<GLShaderProgram>& shader);

        bool ProcessLightSources = true;
        float Shininess;
        glm::vec3 Diffuse;
        glm::vec3 Ambient;
        glm::vec3 Specular;
        Ref<Material> Mat;
    };
}

