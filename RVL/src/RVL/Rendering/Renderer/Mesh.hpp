#pragma once
#include <Core/Core.hpp>
#include <glm/glm.hpp>

namespace Rvl
{
    class GLTexture;
    class GLVertexArray;
    class GLVertexBuffer;
    class GLIndexBuffer;

    struct MeshVertex 
    {
        glm::vec3 Position;
        glm::vec3 Normal;
        glm::vec2 TexCoord;
    };

    struct MeshTexture
    {
        GLuint Id;
        std::string Type; // diffuse / specular
        std::string Filename;
    };

    class Mesh
    {
    public:
        Mesh(const std::vector<MeshVertex>& verticies, const std::vector<uint32>& indicies, const std::vector<MeshTexture>& textures);
        ~Mesh();

        std::vector<MeshTexture> GetTextures() const;
        Ref<GLVertexArray> GetVao() const;

    private:
        void Generate();

        std::vector<MeshVertex> _verticies;
        std::vector<uint32> _indicies;
        std::vector<MeshTexture> _textures;

        Ref<GLVertexArray> _vao;
        Ref<GLVertexBuffer> _vbo;
        Ref<GLIndexBuffer> _ibo;
    };
}

