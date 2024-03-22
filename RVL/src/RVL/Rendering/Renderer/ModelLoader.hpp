#pragma once
#include "Mesh.hpp"
#include "3D/Material.hpp"
#include "RenderEntity.hpp"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

namespace Rvl
{
    class ModelLoader
    {
    public:
        ModelLoader() = default;
        ModelLoader(const std::string& path);
        
        void LoadModel();
        void LoadModel(const std::string& path);
        
        std::vector<Mesh> GetMeshes() const;
        Material GetMaterial() const;
        RenderEntity GetAsEntity() const;

    private:
        mutable std::vector<Mesh> _meshes;
        Material _material;

        std::string _path;
        std::string _directory;
        std::vector<MaterialTexture> _texturesLoaded;
    
    private:
        std::pair<std::vector<Mesh>, Material> ProcessNode(aiNode*, const aiScene*);
        std::pair<Mesh, Material> ProcessMesh(aiMesh*, const aiScene*);
        Material LoadMaterial(aiMaterial*);
        std::vector<MaterialTexture> LoadMaterialTextures(aiMaterial*, aiTextureType, const std::string&);
    };
}

