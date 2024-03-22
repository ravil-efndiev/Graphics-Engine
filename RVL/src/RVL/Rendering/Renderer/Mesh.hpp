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

    class Mesh
    {
    public:
        Mesh(const std::vector<MeshVertex>& verticies, const std::vector<u32>& indicies);
        ~Mesh();

        Ref<GLVertexArray> GetVao() const;

        friend class Renderer3D;

    private:
        void Generate();

        std::vector<MeshVertex> _verticies;
        std::vector<u32> _indicies;

        Ref<GLVertexArray> _vao;
        Ref<GLVertexBuffer> _vbo;
        Ref<GLIndexBuffer> _ibo;

        bool _instanceVboLoaded = false;
    };
}

