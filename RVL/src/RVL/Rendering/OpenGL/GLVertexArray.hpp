#ifndef RVL_GLVERTEXARRAY_HPP
#define RVL_GLVERTEXARRAY_HPP

#include "GLBuffer.hpp"

#define RVL_POSITION_LOCATION 0
#define RVL_COLOR_LOCATION 1
#define RVL_TEXTURE_LOCATION 2

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

        std::shared_ptr<GLIndexBuffer> GetIndexBuffer();

        void BindIndexBuffer();
        void UnbindIndexBuffer();

        void ResetVertexBuffer(int index, GLVertexBuffer& vertexBuffer);

    private:
        GLuint _vertexArrayId;

        int _currentAttribIndex = 0;

        std::vector<std::shared_ptr<GLVertexBuffer>> _vertexBuffers;
        std::shared_ptr<GLIndexBuffer> _indexBuffer;

        void SetAttribPtr(int index, const GLVertexBuffer& vertexBuffer);
    };
}

#endif
