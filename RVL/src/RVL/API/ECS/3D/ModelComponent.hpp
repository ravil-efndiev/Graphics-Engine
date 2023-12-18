#pragma once

#include <Rendering/Renderer/Mesh.hpp>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

namespace Rvl
{
    class Entity;
    class ModelComponent
    {
    public:
        ModelComponent(const std::string& path);
        ModelComponent(const ModelComponent& other);

        void LoadModel(const std::string& path);

        std::vector<Mesh> Meshes;
        std::string Path, Directory;

        friend void ModelLoaderSystem(const std::vector<Entity>&);
        friend class HierarchyWindow;

    private:
        bool _load = false;
    };
}

