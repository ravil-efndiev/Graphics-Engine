#include "Mesh.hpp"

#include "Rendering/OpenGL/GLVertexArray.hpp"
#include "Rendering/OpenGL/GLShaderProgram.hpp"
#include "Rendering/OpenGL/GLTexture.hpp"

#include <stdio.h>
namespace Rvl
{
    Mesh::Mesh(const std::vector<MeshVertex>& verticies, const std::vector<u32>& indicies)
    {
        _verticies = verticies;
        _indicies = indicies;

        Generate();
    }

    Mesh::~Mesh() {}

    void Mesh::Generate()
    {
        _vao = NewRef<GLVertexArray>();

        _vbo = NewRef<GLVertexBuffer>(_verticies);
        _vbo->SetLayout({
            { ElementType::Vec3, 0, sizeof(MeshVertex), false },
            { ElementType::Vec3, offsetof(MeshVertex, Normal), sizeof(MeshVertex), false },
            { ElementType::Vec2, offsetof(MeshVertex, TexCoord), sizeof(MeshVertex), false },
        });

        _ibo = NewRef<GLIndexBuffer>(_indicies);

        _vao->AddVertexBuffer(_vbo);
        _vao->AddIndexBuffer(_ibo);
    }

    Ref<GLVertexArray> Mesh::GetVao() const
    {
        return _vao;
    }

}
