#pragma once
#include <Core/Core.hpp>
#include <Rendering/OpenGL/GLShaderProgram.hpp>
#include <Rendering/Renderer/Mesh.hpp>

namespace Rvl
{
    struct MaterialTexture
    {
        GLuint Id;
        std::string Type;
        std::string Filename;
    };

    class GLShaderProgram;
    struct Material
    {
        Material() = default;
        Material(const Ref<GLShaderProgram>& shader, glm::vec3 ambient, float shininess, glm::vec3 diffuse = glm::vec3(1.f), glm::vec3 specular = glm::vec3(0.5f));
        Material(glm::vec3 ambient, float shininess, glm::vec3 diffuse = glm::vec3(1.f), glm::vec3 specular = glm::vec3(0.5f));
        Material(const Ref<GLShaderProgram>& shader, glm::vec3 ambient, float shininess, std::vector<MaterialTexture> textures, glm::vec3 diffuse = glm::vec3(1.f), glm::vec3 specular = glm::vec3(0.5f));
        Material(glm::vec3 ambient, float shininess, std::vector<MaterialTexture> textures, glm::vec3 diffuse = glm::vec3(1.f), glm::vec3 specular = glm::vec3(0.5f));
        ~Material() {}

        bool ProcessLightSources = true;
        float Shininess;
        glm::vec3 Diffuse;
        glm::vec3 Ambient;
        glm::vec3 Specular;
        Ref<GLShaderProgram> Shader;
        std::vector<MaterialTexture> Textures;

        template <class T> 
        inline void SetUniform(const std::string& name, const T& value)
        {
            Shader->Bind();
            if constexpr (std::is_same<T, float>()) { Shader->SetUniformFloat(name, value); } 
            if constexpr (std::is_same<T, int>()) { Shader->SetUniformInt(name, value); } 
            if constexpr (std::is_same<T, glm::vec2>()) { Shader->SetUniformVec2(name, value); }
            if constexpr (std::is_same<T, glm::vec3>()) { Shader->SetUniformVec3(name, value); }
            if constexpr (std::is_same<T, glm::vec4>()) { Shader->SetUniformVec4(name, value); }
            Shader->Unbind();
        }
    };
}
