#include "MaterialComponent.hpp"

#include <Rendering/OpenGL/GLShaderProgram.hpp>
#include <Rendering/Renderer/ShaderLibrary.hpp>

namespace Rvl
{
    MaterialComponent::MaterialComponent(const Ref<GLShaderProgram>& shader, glm::vec3 ambient, float shininess, glm::vec3 diffuse, glm::vec3 specular)
    {
        Mat = NewRef<Material>(shader);
        Ambient = ambient;
        Shininess = shininess;
        Diffuse = diffuse;
        Specular = specular;
    }

    MaterialComponent::MaterialComponent(glm::vec3 ambient, float shininess, glm::vec3 diffuse, glm::vec3 specular)
    {
        Mat = NewRef<Material>(StandartShaderLib::Get("Light"));
        Ambient = ambient;
        Shininess = shininess;
        Diffuse = diffuse;
        Specular = specular;
    }

    Ref<GLShaderProgram> MaterialComponent::GetShader() const
    {
        return Mat->GetShader();
    }

    void MaterialComponent::SetShader(const Ref<GLShaderProgram>& shader)
    {
        Mat->SetShader(shader);
    }

}
