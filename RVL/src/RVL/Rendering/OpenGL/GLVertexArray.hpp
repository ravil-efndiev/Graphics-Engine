#pragma once

#include "GLBuffer.hpp"

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

        void SetSingleVertexBuffer(const Ref<GLVertexBuffer>& vertexBuffer);

        void AddVertexBuffer(const Ref<GLVertexBuffer>& vertexBuffer);
        void AddIndexBuffer(const Ref<GLIndexBuffer>& indexBuffer);

        void Bind();
        void Unbind();

        Ref<GLIndexBuffer> GetIndexBuffer();

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

