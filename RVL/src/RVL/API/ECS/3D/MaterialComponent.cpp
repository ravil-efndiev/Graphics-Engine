#include "MaterialComponent.hpp"

#include <Rendering/OpenGL/GLShaderProgram.hpp>
#include <Rendering/Renderer/ShaderLibrary.hpp>

namespace Rvl
{
    MaterialComponent::MaterialComponent(const Ref<GLShaderProgram>& shader, glm::vec3 ambient, float shininess, glm::vec3 diffuse, glm::vec3 specular)
    {
        Shader = shader;
        Ambient = ambient;
        Shininess = shininess;
        Diffuse = diffuse;
        Specular = specular;
    }

    MaterialComponent::MaterialComponent(glm::vec3 ambient, float shininess, glm::vec3 diffuse, glm::vec3 specular)
    {
        Shader = StandartShaderLib::Get("Light");
        Ambient = ambient;
        Shininess = shininess;
        Diffuse = diffuse;
        Specular = specular;
    }

    MaterialComponent::MaterialComponent(glm::vec3 ambient, float shininess, std::vector<MaterialTexture> textures, glm::vec3 diffuse, glm::vec3 specular)
    {
        Shader = StandartShaderLib::Get("Light");
        Ambient = ambient;
        Shininess = shininess;
        Diffuse = diffuse;
        Specular = specular;
        Textures = textures;
    }

    MaterialComponent::MaterialComponent(const Ref<GLShaderProgram>& shader, glm::vec3 ambient, float shininess, std::vector<MaterialTexture> textures, glm::vec3 diffuse, glm::vec3 specular)
    {
        Shader = shader;
        Ambient = ambient;
        Shininess = shininess;
        Diffuse = diffuse;
        Specular = specular;
        Textures = textures;
    }


}
