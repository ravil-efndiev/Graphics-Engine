#include "ModelComponent.hpp"
#include <Rendering/OpenGL/GLTexture.hpp>
#include <Rendering/Renderer/Renderer3D.hpp>

namespace Rvl
{
    ModelComponent::ModelComponent(const std::string& path)
    {
        LoadModel(path);
    }

    ModelComponent::ModelComponent(const ModelComponent& other)
    {
        LoadModel(other.Path);
    }

    void ModelComponent::LoadModel(const std::string& path)
    {
        Path = path;
        Directory = Path.substr(0, Path.find_last_of('/'));
        _load = true;
    }

}
