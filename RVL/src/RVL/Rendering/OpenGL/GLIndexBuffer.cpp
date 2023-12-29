#include "GLIndexBuffer.hpp"

namespace Rvl
{
    GLIndexBuffer::GLIndexBuffer(const std::vector<uint32_t>& indicies)
    {
        glGenBuffers(1, &_bufferId);
        glBindBuffer(GL_ARRAY_BUFFER, _bufferId);
        glBufferData(GL_ARRAY_BUFFER, indicies.size() * sizeof(uint32_t), indicies.data(), GL_STATIC_DRAW);   
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

    int GLIndexBuffer::GetIndiciesCount()
    {
        return _indiciesCount;
    }
}