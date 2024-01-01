#include "GLVertexBuffer.hpp"

namespace Rvl
{
    GLVertexBuffer::GLVertexBuffer()
    {
        glGenBuffers(1, &_bufferId);
    }

    GLVertexBuffer::GLVertexBuffer(size_t size, int components, bool normalized) : _normalized(normalized)
    {
        _verticiesCount = components;
        CreateBuffer(size);
    }

    GLVertexBuffer::~GLVertexBuffer()
    {
        glDeleteBuffers(1, &_bufferId);
    }

    void GLVertexBuffer::CreateBuffer(size_t size)
    {
        glGenBuffers(1, &_bufferId);
        glBindBuffer(GL_ARRAY_BUFFER, _bufferId);
        glBufferData(GL_ARRAY_BUFFER, size, nullptr, GL_DYNAMIC_DRAW );
    }

    void GLVertexBuffer::Bind()
    {
        glBindBuffer(GL_ARRAY_BUFFER, _bufferId);
    }

    void GLVertexBuffer::Unbind()
    {
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    void GLVertexBuffer::SetData(void* data, size_t size)
    {
        glBindBuffer(GL_ARRAY_BUFFER, _bufferId);
        glBufferSubData(GL_ARRAY_BUFFER, 0, size, data);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    void GLVertexBuffer::ReallocData(void* data, size_t size)
    {
        glBindBuffer(GL_ARRAY_BUFFER, _bufferId);
        glBufferData(GL_ARRAY_BUFFER, size, data, GL_DYNAMIC_DRAW);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    int GLVertexBuffer::GetVerticiesCount() const
    {
        return _verticiesCount;
    }

    bool GLVertexBuffer::GetNormalized() const
    {
        return _normalized;
    }

    GLuint GLVertexBuffer::GetId() const
    {
        return _bufferId;
    }

    void GLVertexBuffer::SetLayout(const std::initializer_list<LayoutElement>& layout)
    {
        _layout = layout;
    }

    std::vector<LayoutElement> GLVertexBuffer::GetLayout() const
    {
        return _layout;
    }

    bool GLVertexBuffer::IsLayoutUsed() const
    {
        return !_layout.empty();
    }
}
