#include "ShaderLibrary.hpp"
#include <Rendering/OpenGL/GLShaderProgram.hpp>

namespace Rvl
{
    void ShaderLibrary::Add(const std::string& name, const Ref<GLShaderProgram>& shader)
    {
        RVL_ASSERT((_shaders.find(name) == _shaders.end()), "Shader with this name already exists");
        _shaders[name] = shader;        
    }
    
    Ref<GLShaderProgram> ShaderLibrary::Load(const std::string& name, const std::string& path)
    {
        RVL_ASSERT((_shaders.find(name) == _shaders.end()), "Shader with this name already exists");
        Ref<GLShaderProgram> shader = NewRef<GLShaderProgram>(path);
        _shaders[name] = shader;        
        return shader;
    }
    
    Ref<GLShaderProgram> ShaderLibrary::Get(const std::string& name)
    {
        auto it = _shaders.find(name);
        if (it != _shaders.end())
            return it->second;
        return nullptr;
    }

    Ref<ShaderLibrary> StandartShaderLib::_lib;

    Ref<GLShaderProgram> StandartShaderLib::Get(const std::string& name)
    {
        return _lib->Get(name);
    }
    
    void StandartShaderLib::Init()
    {
        _lib = NewRef<ShaderLibrary>();
        _lib->Load("Light", "standart_assets/shaders/mesh");
        _lib->Load("Screen", "standart_assets/shaders/screen");
        //_lib->Load("Particle", "standart_assets/shaders/particle");
    }
}
