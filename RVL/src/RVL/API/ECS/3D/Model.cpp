#include "Model.hpp"
#include <Rendering/OpenGL/GLTexture.hpp>
#include <Rendering/Renderer/Renderer3D.hpp>

namespace Rvl
{
    Model::Model(const std::string& path)
    {
        LoadModel(path);
    }

    Model::Model(const Model& other)
    {
        LoadModel(other.Path);
    }

    void Model::LoadModel(const std::string& path)
    {
        Path = path;
        Directory = Path.substr(0, Path.find_last_of('/'));
        _load = true;
    }

}
