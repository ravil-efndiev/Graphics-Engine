#include "GLVertexArray.hpp"

#include <Core/Core.hpp>
#include <Rvlglpch.hpp>

namespace Rvl
{
    GLVertexArray::GLVertexArray()
    {
        glGenVertexArrays(1, &_vertexArrayId);
        Bind();
    }

    GLVertexArray::~GLVertexArray()
    {   
        glDeleteVertexArrays(1, &_vertexArrayId);
    }

    void GLVertexArray::SetSingleVertexBuffer(const Ref<GLVertexBuffer>& vertexBuffer)
    {
        RVL_ASSERT(vertexBuffer->IsLayoutUsed(), "Vertex buffer doesn't have a proper layout");

        Bind();
        vertexBuffer->Bind();

        auto layout = vertexBuffer->GetLayout();

        for (int i = 0; i < layout.size(); i++)
        {
            glEnableVertexAttribArray(i);

            glVertexAttribPointer(i,
                    static_cast<int>(layout[i].Type),
                    GL_FLOAT, 
                    layout[i].Normalized,
                    layout[i].Size, (void*)layout[i].Offset);
        }   

        vertexBuffer->Unbind();

    }

    void GLVertexArray::AddVertexBuffer(const Ref<GLVertexBuffer>& vertexBuffer)
    {
        Bind();
        vertexBuffer->Bind();

        glVertexAttribPointer(_currentAttribIndex,
                vertexBuffer->GetVerticiesCount(),
                GL_FLOAT, 
                vertexBuffer->GetNormalized(),
                vertexBuffer->GetVerticiesCount() * sizeof(float), nullptr);

        glEnableVertexAttribArray(_currentAttribIndex);

        _vertexBuffers.push_back(vertexBuffer);
        _currentAttribIndex++;
    }

    void GLVertexArray::AddIndexBuffer(const Ref<GLIndexBuffer>& indexBuffer)
    {
        Bind();
        indexBuffer->Bind();
        
        _indexBuffer = indexBuffer;
    }

    void GLVertexArray::Bind()
    {
        glBindVertexArray(_vertexArrayId);
    }

    void GLVertexArray::Unbind()
    {
        glBindVertexArray(0);
    }

    Ref<GLIndexBuffer> GLVertexArray::GetIndexBuffer()
    {
        return _indexBuffer;
    }

    void GLVertexArray::BindIndexBuffer()
    {
        _indexBuffer->Bind();
    }

    void GLVertexArray::UnbindIndexBuffer()
    {
        _indexBuffer->Unbind();
    }

    void GLVertexArray::ResetVertexBuffer(int index, GLVertexBuffer& vertexBuffer)
    {
        Bind();
        vertexBuffer.Bind();

        SetAttribPtr(index, vertexBuffer);

        vertexBuffer.Unbind();
        Unbind();
    }

    void GLVertexArray::SetAttribPtr(int index, const GLVertexBuffer& vertexBuffer)
    {
        glVertexAttribPointer(index,
            vertexBuffer.GetVerticiesCount(),
            GL_FLOAT, 
            vertexBuffer.GetNormalized(),
            vertexBuffer.GetVerticiesCount() * sizeof(float), nullptr);

        glEnableVertexAttribArray(index);

        glBindBufferBase(GL_ARRAY_BUFFER, index, vertexBuffer.GetId());
    }
}
