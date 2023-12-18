#include "Material.hpp"

#include <Rendering/OpenGL/GLShaderProgram.hpp>
#include <Rendering/Renderer/ShaderLibrary.hpp>

namespace Rvl
{
    Material::Material(const Ref<GLShaderProgram>& shader, glm::vec3 ambient, float shininess, glm::vec3 diffuse, glm::vec3 specular)
    {
        Shader = shader;
        Ambient = ambient;
        Shininess = shininess;
        Diffuse = diffuse;
        Specular = specular;
    }

    Material::Material(glm::vec3 ambient, float shininess, glm::vec3 diffuse, glm::vec3 specular)
    {
        Shader = StandartShaderLib::Get("Light");
        Ambient = ambient;
        Shininess = shininess;
        Diffuse = diffuse;
        Specular = specular;
    }

    Material::Material(glm::vec3 ambient, float shininess, std::vector<MaterialTexture> textures, glm::vec3 diffuse, glm::vec3 specular)
    {
        Shader = StandartShaderLib::Get("Light");
        Ambient = ambient;
        Shininess = shininess;
        Diffuse = diffuse;
        Specular = specular;
        Textures = textures;
    }

    Material::Material(const Ref<GLShaderProgram>& shader, glm::vec3 ambient, float shininess, std::vector<MaterialTexture> textures, glm::vec3 diffuse, glm::vec3 specular)
    {
        Shader = shader;
        Ambient = ambient;
        Shininess = shininess;
        Diffuse = diffuse;
        Specular = specular;
        Textures = textures;
    }


}
