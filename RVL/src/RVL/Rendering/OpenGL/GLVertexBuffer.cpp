#include "GLVertexBuffer.hpp"

namespace Rvl
{
    GLVertexBuffer::GLVertexBuffer(size_t size, int components, bool normalized) : _normalized(normalized)
    {
        _verticiesCount = components;
        CreateBuffer(size);
    }

    GLVertexBuffer::GLVertexBuffer(const std::vector<float>& verticies, bool normalized)
        : _normalized(normalized)
    {
        CreateBuffer(verticies, 1);
    }

    GLVertexBuffer::GLVertexBuffer(const std::vector<glm::vec2>& verticies, bool normalized)
        : _normalized(normalized)
    {
        CreateBuffer(verticies, 2);
    }

    GLVertexBuffer::GLVertexBuffer(const std::vector<glm::vec3>& verticies, bool normalized)
        : _normalized(normalized)
    {
        CreateBuffer(verticies, 3);
    }

    GLVertexBuffer::GLVertexBuffer(const std::vector<glm::vec4>& verticies, bool normalized)
        : _normalized(normalized)
    {
        CreateBuffer(verticies, 4);
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

    template <class T>
    inline void GLVertexBuffer::CreateBuffer(const std::vector<T> &verticies, int verticiesCount)
    {
        _verticiesCount = verticiesCount;

        glGenBuffers(1, &_bufferId);
        glBindBuffer(GL_ARRAY_BUFFER, _bufferId);
        glBufferData(GL_ARRAY_BUFFER, verticies.size() * sizeof(T), verticies.data(), GL_STATIC_DRAW);
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
