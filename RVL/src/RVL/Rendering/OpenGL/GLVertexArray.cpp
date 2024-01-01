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
        for (int i = 0; i < _currentAttribIndex; i++)
            glDisableVertexAttribArray(i);
        glDeleteVertexArrays(1, &_vertexArrayId);
    }

    void GLVertexArray::AddVertexBuffer(const Ref<GLVertexBuffer>& vertexBuffer, bool perInstance)
    {
        Bind();
        vertexBuffer->Bind();

        if (vertexBuffer->IsLayoutUsed())
        {
            auto layout = vertexBuffer->GetLayout();

            for (int i = 0; i < layout.size(); i++)
            {
                if (layout[i].Type == ElementType::Mat4)
                {
                    uint16 count = static_cast<uint16>(layout[i].Type);
					for (uint16 j = 0; j < count; j++)
					{
						glEnableVertexAttribArray(_currentAttribIndex);
						glVertexAttribPointer(_currentAttribIndex,
							count,
							GL_FLOAT,
							layout[i].Normalized,
							layout[i].Size,
							(void*)(layout[i].Offset + sizeof(float) * count * j));

                        if (perInstance)
						    glVertexAttribDivisor(_currentAttribIndex, 1);
                            
						_currentAttribIndex++;
					}
                }
                else
                {
                    _currentAttribIndex++;
                    glEnableVertexAttribArray(i);

                    glVertexAttribPointer(i,
                        static_cast<int>(layout[i].Type),
                        GL_FLOAT, 
                        layout[i].Normalized,
                        layout[i].Size, (void*)layout[i].Offset);

                    if (perInstance)
                        glVertexAttribDivisor(_currentAttribIndex, 1);

                }
            }   
        }
        else
        {
            glVertexAttribPointer(_currentAttribIndex,
                vertexBuffer->GetVerticiesCount(),
                GL_FLOAT, 
                vertexBuffer->GetNormalized(),
                vertexBuffer->GetVerticiesCount() * sizeof(float), nullptr);

            glEnableVertexAttribArray(_currentAttribIndex);

            if (perInstance)
                glVertexAttribDivisor(_currentAttribIndex, 1);

            _currentAttribIndex++;
        }
        vertexBuffer->Unbind();
        _vertexBuffers.push_back(vertexBuffer);
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

    std::vector<Ref<GLVertexBuffer>> GLVertexArray::GetVertexBuffers()
    {
        return _vertexBuffers;
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
