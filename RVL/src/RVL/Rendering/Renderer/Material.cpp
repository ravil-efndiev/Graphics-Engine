#include "Material.hpp"

#include <Rendering/OpenGL/GLShaderProgram.hpp>

namespace Rvl
{
    Material::Material(const Ref<GLShaderProgram>& shader)
    {
        RVL_ASSERT(shader, "Creating material with a nullptr shader");
        _shader = shader;
    }

    Material::Material(const Material& other)
    {
        _shader = other._shader;
        _floats = other._floats;
        _vec2s = other._vec2s;
        _vec3s = other._vec3s;
        _vec4s = other._vec4s;
    }

    Ref<GLShaderProgram> Material::GetShader() const
    {
        return _shader;
    }

    void Material::SetShader(const Ref<GLShaderProgram>& shader)
    {
        RVL_ASSERT(shader, "Shader you were trying to set for material is nullptr");
        _shader = shader;
    }

    void Material::Update()
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
