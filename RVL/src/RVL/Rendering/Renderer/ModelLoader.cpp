#include "ModelLoader.hpp"
#include "ShaderLibrary.hpp"
#include "Rendering/OpenGL/GLTexture.hpp"

namespace Rvl
{

    ModelLoader::ModelLoader(const std::string& path)
    {
        _path = path;
    }

    void ModelLoader::LoadModel()
    {
        if (!_path.empty())
            LoadModel(_path);
    }

    std::vector<Mesh> ModelLoader::GetMeshes() const
    {
        return _meshes;
    }

    Material ModelLoader::GetMaterial() const
    {
        return _material;
    }

    void ModelLoader::LoadModel(const std::string& path)
    {
        _path = path;
        _directory = path.substr(0, path.find_last_of('/'));

        Assimp::Importer importer;
        const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate);	

        if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) 
            throw Error(std::string("Assimp error:") + importer.GetErrorString(), RVL_INTERNAL_ERROR);

        auto result = ProcessNode(scene->mRootNode, scene);
        _meshes = result.first;
        _material = result.second;
    }

    std::pair<std::vector<Mesh>, Material> ModelLoader::ProcessNode(aiNode* node, const aiScene* scene)
    {
        std::vector<Mesh> meshes;
        Material mat;

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
            mat.UseTexture = result.second.UseTexture;
            mat.Shader = result.second.Shader;
        }
        
        return std::make_pair(meshes, mat);
    }

    std::pair<Mesh, Material> ModelLoader::ProcessMesh(aiMesh* mesh, const aiScene* scene)
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

        Material material;
        if (scene->mNumMaterials > mesh->mMaterialIndex)
        {
            aiMaterial* mat = scene->mMaterials[mesh->mMaterialIndex];

            material = LoadMaterial(mat);
        }

        return std::make_pair(Mesh(vertices, indices), material);
    }

    Material ModelLoader::LoadMaterial(aiMaterial* mat) 
    {
        Material material;
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

        if (mat->GetTextureCount(aiTextureType_DIFFUSE) > 0)
        {
            std::vector<MaterialTexture> diffuseMaps = LoadMaterialTextures(mat, aiTextureType_DIFFUSE, RVL_TEXTURE_DIFFUSE);
            textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());

            std::vector<MaterialTexture> specularMaps = LoadMaterialTextures(mat, aiTextureType_SPECULAR, RVL_TEXTURE_DIFFUSE);
            textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());

            material.Textures = textures;
            material.UseTexture = true;
        }
        else
        {
            material.UseTexture = false;
        }
        
        return material;
    }

    std::vector<MaterialTexture> ModelLoader::LoadMaterialTextures(aiMaterial* mat, aiTextureType type, const std::string& typeName)
    {
        std::vector<MaterialTexture> textures;

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
                MaterialTexture texture = 
                {
                    GLTexture::TextureFromFile(_directory + '/' + filename.C_Str()),
                    typeName, filename.C_Str(), _directory + '/' + filename.C_Str()
                };

                textures.push_back(texture);
                _texturesLoaded.push_back(texture);
            }
        }
        return textures;
    }

}
