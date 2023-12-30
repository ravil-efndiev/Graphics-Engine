#pragma once

#include "GLVertexBuffer.hpp"
#include "GLIndexBuffer.hpp"

#define RVL_POSITION_LOCATION 0
#define RVL_COLOR_LOCATION 1
#define RVL_TEXTURE_LOCATION 2

namespace Rvl
{
    class GLVertexArray
    {
    public:
        GLVertexArray();
        ~GLVertexArray();

        void AddVertexBuffer(const Ref<GLVertexBuffer>& vertexBuffer, bool perInstance = false);
        void AddIndexBuffer(const Ref<GLIndexBuffer>& indexBuffer);

        void Bind();
        void Unbind();

        Ref<GLIndexBuffer> GetIndexBuffer();
        std::vector<Ref<GLVertexBuffer>> GetVertexBuffers();

        void BindIndexBuffer();
        void UnbindIndexBuffer();

        void ResetVertexBuffer(int index, GLVertexBuffer& vertexBuffer);

    private:
        GLuint _vertexArrayId;

        int _currentAttribIndex = 0;

        std::vector<Ref<GLVertexBuffer>> _vertexBuffers;
        Ref<GLIndexBuffer> _indexBuffer;

        void SetAttribPtr(int index, const GLVertexBuffer& vertexBuffer);
    };
}

