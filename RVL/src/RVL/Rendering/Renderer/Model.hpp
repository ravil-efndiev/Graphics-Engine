#pragma once

#include "Mesh.hpp"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

namespace Rvl
{
    class GLShaderProgram;

    class Model 
    {
        public:
            Model(const std::string& path);

            void Draw(const Ref<GLShaderProgram>& shader);	

        private:
            std::vector<Mesh> _meshes;
            std::string _directory;
            std::vector<MeshTexture> _texturesLoaded;

            void LoadModel(const std::string& path);
            void ProcessNode(aiNode* node, const aiScene* scene);
            Mesh ProcessMesh(aiMesh* mesh, const aiScene* scene);
            std::vector<MeshTexture> LoadMaterialTextures(aiMaterial* mat, aiTextureType type, const std::string& typeName);
    };
}

