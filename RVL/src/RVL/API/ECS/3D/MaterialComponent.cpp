#include "MaterialComponent.hpp"

#include <Rendering/OpenGL/GLShaderProgram.hpp>

namespace Rvl
{
    MaterialComponent::MaterialComponent(const Ref<GLShaderProgram>& shader)
    {
        RVL_ASSERT(shader, "Creating material with a nullptr shader");
        _shader = shader;
    }

    MaterialComponent::MaterialComponent(const MaterialComponent& other)
    {
        _shader = other._shader;
        _floats = other._floats;
        _vec2s = other._vec2s;
        _vec3s = other._vec3s;
        _vec4s = other._vec4s;
        _processLightSources = other._processLightSources;
    }

    Ref<GLShaderProgram> MaterialComponent::GetShader() const
    {
        return _shader;
    }

    void MaterialComponent::SetShader(const Ref<GLShaderProgram>& shader)
    {
        RVL_ASSERT(shader, "Shader you were trying to set for material is nullptr");
        _shader = shader;
    }

    void MaterialComponent::ProcessLightSources(bool flag)
    {
        _processLightSources = flag;
    }

    bool MaterialComponent::ShouldProcessLightSources() const
    {

        return _processLightSources;
    }

    void MaterialComponent::Update()
    {
        _shader->Bind();
        for (const auto& el : _floats) 
        {
            _shader->SetUniformFloat(el.first, el.second);
        }
        for (const auto& el : _vec2s) 
        {
            _shader->SetUniformVec2(el.first, el.second);
        }
        for (const auto& el : _vec3s) 
        {
            _shader->SetUniformVec3(el.first, el.second);
        }
        for (const auto& el : _vec4s) 
        {
            _shader->SetUniformVec4(el.first, el.second);
        }
    }
}
