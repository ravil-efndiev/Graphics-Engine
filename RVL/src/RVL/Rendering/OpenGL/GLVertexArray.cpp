#include "GLVertexArray.hpp"

#include <Platform.hpp>
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
        vertexBuffer->Bind();

        glVertexAttribPointer(_vertexBuffers.size(),
                vertexBuffer->GetVerticiesCount(),
                GL_FLOAT, 
                vertexBuffer->GetNormalized(),
                0, nullptr);

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
        for (int i = 0; i < _vertexBuffers.size(); i++)
        {
            glEnableVertexAttribArray(i);
        }
     
        _indexBuffer->Bind();
        glDrawElements(GL_TRIANGLES, _indexBuffer->GetIndiciesCount(), GL_UNSIGNED_INT, nullptr);
        
        for (int i = 0; i < _vertexBuffers.size(); i++)
        {
            glDisableVertexAttribArray(i);
        }
    }
}
