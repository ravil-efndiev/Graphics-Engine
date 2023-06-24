#include "Model.hpp"
#include <Rendering/OpenGL/GLTexture.hpp>
#include "Renderer3D.hpp"

namespace Rvl
{
    Model::Model(const std::string& path)
    {
        LoadModel(path);
    }

    void Model::Draw(const Ref<GLShaderProgram>& shader)
    {
        for (const auto& mesh : _meshes)
            Renderer3D::SubmitMesh(mesh, shader);
    }

    void Model::LoadModel(const std::string& path)
    {
        Assimp::Importer importer;
        const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate);	

        if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) 
            throw Error(std::string("Assimp error:") + importer.GetErrorString(), RVL_INTERNAL_ERROR);

        _directory = path.substr(0, path.find_last_of('/'));

        ProcessNode(scene->mRootNode, scene);
    }
    
    void Model::ProcessNode(aiNode* node, const aiScene* scene)
    {
        for (int i = 0; i < node->mNumMeshes; i++)
        {
            aiMesh* mesh = scene->mMeshes[node->mMeshes[i]]; 
            _meshes.push_back(ProcessMesh(mesh, scene));			
        }

        for (int i = 0; i < node->mNumChildren; i++)
        {
            ProcessNode(node->mChildren[i], scene);
        }
    }
    
    Mesh Model::ProcessMesh(aiMesh* mesh, const aiScene* scene)
    {
        std::vector<MeshVertex> vertices;
        std::vector<uint32> indices;
        std::vector<MeshTexture> textures;

        for (int i = 0; i < mesh->mNumVertices; i++)
        {
            MeshVertex vertex;

            vertex.Position = glm::vec3(mesh->mVertices[i].x,  mesh->mVertices[i].y, mesh->mVertices[i].z);

            if (mesh->HasNormals())
                vertex.Normal = glm::vec3(mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z);

            if (mesh->mTextureCoords[0])
                vertex.TexCoord = glm::vec2(mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y);
            else
                vertex.TexCoord = glm::vec2(0.f, 0.f);  

            vertices.push_back(vertex);
        }

        for (int i = 0; i < mesh->mNumFaces; i++)
        {
            aiFace face = mesh->mFaces[i];
            
            for (int j = 0; j < face.mNumIndices; j++)
                indices.push_back(face.mIndices[j]);
        }  

        if (mesh->mMaterialIndex >= 0)
        {
            aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];

            std::vector<MeshTexture> diffuseMaps = LoadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");
            textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());

            std::vector<MeshTexture> specularMaps = LoadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular");

            textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
        }

        return Mesh(vertices, indices, textures);
    }
    
    std::vector<MeshTexture> Model::LoadMaterialTextures(aiMaterial* mat, aiTextureType type, const std::string& typeName)
    {
        std::vector<MeshTexture> textures;

        for(int i = 0; i < mat->GetTextureCount(type); i++)
        {
            aiString filename;
            mat->GetTexture(type, i, &filename);
            bool skip = false;

            for (const auto& tex : _texturesLoaded)
            {
                if (tex.Filename == filename.C_Str())
                {
                    textures.push_back(tex);
                    skip = true;
                    break;
                }
            }

            if (!skip)
            {
                MeshTexture texture = 
                {
                    GLTexture::TextureFromFile(_directory + '/' + filename.C_Str()),
                    typeName, filename.C_Str()
                };

                textures.push_back(texture);
                _texturesLoaded.push_back(texture);
            }
        }
        return textures;
    }
}
