#include "GLIndexBuffer.hpp"

namespace Rvl
{
    GLIndexBuffer::GLIndexBuffer(const std::vector<u32>& indicies)
    {
        glGenBuffers(1, &_bufferId);
        glBindBuffer(GL_ARRAY_BUFFER, _bufferId);
        glBufferData(GL_ARRAY_BUFFER, indicies.size() * sizeof(u32), indicies.data(), GL_STATIC_DRAW);   
        _indiciesCount = indicies.size();
    }

    GLIndexBuffer::~GLIndexBuffer()
    {
        glDeleteBuffers(1, &_bufferId);
    }

    void GLIndexBuffer::Bind()
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _bufferId);
    }

    void GLIndexBuffer::Unbind()
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }

    u32 GLIndexBuffer::GetIndiciesCount()
    {
        return _indiciesCount;
    }
}