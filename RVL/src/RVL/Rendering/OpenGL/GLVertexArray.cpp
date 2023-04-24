#include "GLVertexArray.hpp"

#include <Core/Core.hpp>
#include <Rvlglpch.hpp>

namespace rvl
{
    GLVertexArray::GLVertexArray()
    {
        glGenVertexArrays(1, &_vertexArrayId);
        Bind();
    }

    GLVertexArray::~GLVertexArray()
    {   
        for (int i = 0; i < _vertexBuffers.size(); i++)
        {
            glDisableVertexAttribArray(i);
        }
        glDeleteVertexArrays(1, &_vertexArrayId);
    }

    void GLVertexArray::AddVertexBuffer(const std::shared_ptr<GLVertexBuffer>& vertexBuffer)
    {
        Bind();
        vertexBuffer->Bind();

        glVertexAttribPointer(_vertexBuffers.size(),
                vertexBuffer->GetVerticiesCount(),
                GL_FLOAT, 
                vertexBuffer->GetNormalized(),
                vertexBuffer->GetVerticiesCount() * sizeof(float), nullptr);

        glEnableVertexAttribArray(_vertexBuffers.size());

        _vertexBuffers.push_back(vertexBuffer);
    }

    void GLVertexArray::AddIndexBuffer(const std::shared_ptr<GLIndexBuffer>& indexBuffer)
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

    void GLVertexArray::Draw()
    {     
        Bind();

        _indexBuffer->Bind();
        glDrawElements(GL_TRIANGLES, _indexBuffer->GetIndiciesCount(), GL_UNSIGNED_INT, nullptr);
        _indexBuffer->Unbind();

        Unbind();
    }

    std::shared_ptr<GLIndexBuffer> GLVertexArray::GetIndexBuffer()
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
