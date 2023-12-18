#include "StandartSystems.hpp"

#include "2D/SpriteComponent.hpp"
#include "2D/MovementComponent.hpp"
#include "2D/AnimationComponent.hpp"
#include "3D/MaterialComponent.hpp"
#include "3D/DirectionalLightComponent.hpp"
#include "3D/ModelComponent.hpp"
#include "3D/PointLightComponent.hpp"
#include "General/TransformComponent.hpp"

#include <Rendering/Renderer/Mesh.hpp>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <Rendering/OpenGL/GLTexture.hpp>
#include <Rendering/Renderer/ShaderLibrary.hpp>
#include <Rendering/Renderer/Renderer3D.hpp>

namespace Rvl
{
    static std::string directory;
    static std::vector<MaterialTexture> texturesLoaded;

    std::pair<std::vector<Mesh>, MaterialComponent> LoadModel(const std::string&);
    std::pair<std::vector<Mesh>, MaterialComponent> ProcessNode(aiNode*, const aiScene*);
    std::pair<Mesh, MaterialComponent> ProcessMesh(aiMesh*, const aiScene*);
    MaterialComponent LoadMaterial(aiMaterial* mat);
    std::vector<MaterialTexture> LoadMaterialTextures(aiMaterial*, aiTextureType, const std::string&);

    void ModelLoaderSystem(const std::vector<Entity>& entities)
    {
        for (auto entity : entities)
        {
            if (!entity.Has<ModelComponent>())
                continue;
            
            auto& model = entity.Get<ModelComponent>();
            
            if (model._load) 
            {
                texturesLoaded.clear();
                directory = model.Directory;
                auto result = LoadModel(model.Path);
                model.Meshes = result.first;
                if (!entity.Has<MaterialComponent>())
                {
                    entity.Add<MaterialComponent>(
                        result.second.Shader,
                        result.second.Ambient,
                        result.second.Shininess,
                        result.second.Textures,
                        result.second.Diffuse,
                        result.second.Specular
                    );
                    RVL_LOG(result.second.Shininess);
                }
                else
                {
                    auto& mat = entity.Get<MaterialComponent>();
                    if (mat.Textures.empty())
                    {
                        RVL_LOG(result.second.Diffuse.r);
                        mat.Textures = result.second.Textures;
                    }
                }
                model._load = false;
            }
        }
    }

    std::pair<std::vector<Mesh>, MaterialComponent> LoadModel(const std::string& path)
    {
        Assimp::Importer importer;
        const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate);	

        if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) 
            throw Error(std::string("Assimp error:") + importer.GetErrorString(), RVL_INTERNAL_ERROR);

        return ProcessNode(scene->mRootNode, scene);
    }

    std::pair<std::vector<Mesh>, MaterialComponent> ProcessNode(aiNode* node, const aiScene* scene)
    {
        std::vector<Mesh> meshes;
        MaterialComponent mat;

        for (int i = 0; i < node->mNumMeshes; i++)
        {
            aiMesh* mesh = scene->mMeshes[node->mMeshes[i]]; 
            auto result = ProcessMesh(mesh, scene);
            meshes.push_back(result.first);
            mat = result.second;
        }

        for (int i = 0; i < node->mNumChildren; i++)
        {
            auto result = ProcessNode(node->mChildren[i], scene);
            meshes.insert(meshes.end(), result.first.begin(), result.first.end());
            mat.Textures = result.second.Textures;
            mat.Ambient = result.second.Ambient;
            mat.Diffuse = result.second.Diffuse;
            mat.Specular = result.second.Specular;
            mat.Shininess = result.second.Shininess;
            mat.Shader = result.second.Shader;
        }
        
        return std::make_pair(meshes, mat);
    }

    std::pair<Mesh, MaterialComponent> ProcessMesh(aiMesh* mesh, const aiScene* scene)
    {
        std::vector<MeshVertex> vertices;
        std::vector<uint32> indices;
        std::vector<MaterialTexture> textures;

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

        MaterialComponent material;
        if (scene->mNumMaterials > mesh->mMaterialIndex)
        {
            aiMaterial* mat = scene->mMaterials[mesh->mMaterialIndex];

            material = LoadMaterial(mat);
        }

        return std::make_pair(Mesh(vertices, indices), material);
    }

    MaterialComponent LoadMaterial(aiMaterial* mat) 
    {
        MaterialComponent material;
        aiColor3D color(0.f, 0.f, 0.f);
        float shininess;
        std::vector<MaterialTexture> textures;
        
        material.Shader = StandartShaderLib::Get("Light");

        mat->Get(AI_MATKEY_COLOR_DIFFUSE, color);
        material.Diffuse = glm::vec3(color.r, color.b, color.g);

        mat->Get(AI_MATKEY_COLOR_AMBIENT, color);
        material.Ambient = glm::vec3(color.r, color.b, color.g);

        mat->Get(AI_MATKEY_COLOR_SPECULAR, color);
        material.Specular = glm::vec3(color.r, color.b, color.g);

        mat->Get(AI_MATKEY_SHININESS, shininess);
        material.Shininess = shininess;

        std::vector<MaterialTexture> diffuseMaps = LoadMaterialTextures(mat, aiTextureType_DIFFUSE, "texture_diffuse");
        textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());

        std::vector<MaterialTexture> specularMaps = LoadMaterialTextures(mat, aiTextureType_SPECULAR, "texture_specular");
        textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());

        material.Textures = textures;

        return material;
    }

    std::vector<MaterialTexture> LoadMaterialTextures(aiMaterial* mat, aiTextureType type, const std::string& typeName)
    {
        std::vector<MaterialTexture> textures;

        for(int i = 0; i < mat->GetTextureCount(type); i++)
        {
            aiString filename;
            mat->GetTexture(type, i, &filename);
            bool skip = false;

            for (const auto& tex : texturesLoaded)
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
                MaterialTexture texture = 
                {
                    GLTexture::TextureFromFile(directory + '/' + filename.C_Str()),
                    typeName, filename.C_Str()
                };

                textures.push_back(texture);
                texturesLoaded.push_back(texture);
            }
        }
        return textures;
    }
}
