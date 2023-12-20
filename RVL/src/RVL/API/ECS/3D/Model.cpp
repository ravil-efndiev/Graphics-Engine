#include "Model.hpp"
#include <Rendering/OpenGL/GLTexture.hpp>
#include <Rendering/Renderer/StandartMeshes.hpp>

namespace Rvl
{
    Model::Model(const std::string& path)
    {
        LoadModel(path);
    }

    Model::Model(const Model& other)
    {
        Meshes = other.Meshes;
        Path = other.Path;
        Type = other.Type;
    }

    void Model::LoadModel(const std::string& path)
    {
        Type = MeshType::Custom;
        Path = path;
        _load = true;
    }

}
