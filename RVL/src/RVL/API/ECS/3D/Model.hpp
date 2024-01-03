#pragma once

#include <Rendering/Renderer/StandartMeshes.hpp>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

namespace Rvl
{
    enum MeshType 
    {
        Cube, Sphere, Cylinder, Custom
    };

    class Entity;
    class Model
    {
    public:

        Model() = default;
        Model(const std::string& path);
        Model(const Model& other);

        void LoadModel(const std::string& path);

        std::vector<Mesh> Meshes;
        std::vector<Mesh> MeshesSaved;
        std::string Path;
        MeshType Type = MeshType::Cube;

        bool RepeatUV = false;

        friend void ModelLoaderSystem(const std::vector<Entity>&);
        friend class HierarchyWindow;

    private:
        bool _load = false;
    };
}

