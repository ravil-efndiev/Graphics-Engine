#ifndef RVL_GLVERTEXARRAY_HPP
#define RVL_GLVERTEXARRAY_HPP

#include "GLBuffer.hpp"

namespace rvl
{
    class GLVertexArray
    {
    public:
        GLVertexArray();
        ~GLVertexArray();

        void AddVertexBuffer(const std::shared_ptr<GLVertexBuffer>& vertexBuffer);
        void AddIndexBuffer(const std::shared_ptr<GLIndexBuffer>& indexBuffer);

        void Bind();
        void Unbind();

        void Draw();

    private:
        GLuint _vertexArrayId;

        int _currentAttribIndex = 0;

        std::vector<std::shared_ptr<GLVertexBuffer>> _vertexBuffers;
        std::shared_ptr<GLIndexBuffer> _indexBuffer;
    };
}

#endif
