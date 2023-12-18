#pragma once

#include <Rendering/Renderer/Mesh.hpp>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

namespace Rvl
{
    class Entity;
    class Model
    {
    public:
        Model(const std::string& path);
        Model(const Model& other);

        void LoadModel(const std::string& path);

        std::vector<Mesh> Meshes;
        std::string Path, Directory;

        friend void ModelLoaderSystem(const std::vector<Entity>&);
        friend class HierarchyWindow;

    private:
        bool _load = false;
    };
}

