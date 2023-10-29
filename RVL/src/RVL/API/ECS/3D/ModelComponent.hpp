#pragma once

#include <Rendering/Renderer/Mesh.hpp>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

namespace Rvl
{
    class ModelComponent
    {
    public:
        ModelComponent(const std::string& path);

        std::vector<Mesh> GetMeshes() const;

        friend class InspectorWindow;
    private:
        std::vector<Mesh> _meshes;
        std::string _path, _directory;
        std::vector<MeshTexture> _texturesLoaded;

        void LoadModel(const std::string& path);
        void ProcessNode(aiNode* node, const aiScene* scene);
        Mesh ProcessMesh(aiMesh* mesh, const aiScene* scene);
        std::vector<MeshTexture> LoadMaterialTextures(aiMaterial* mat, aiTextureType type, const std::string& typeName);
    };
}

