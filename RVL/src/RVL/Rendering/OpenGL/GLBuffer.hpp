#ifndef RVL_GLBUFFER_HPP
#define RVL_GLBUFFER_HPP

#include <Rvlglpch.hpp>
#include <Core/Core.hpp>

namespace rvl
{
    // should be used only once per layout element
    class GLVertexBuffer
    {
    public:
        GLVertexBuffer(const std::vector<float>& verticies, bool normalized = GL_FALSE);
        GLVertexBuffer(const std::vector<glm::vec2>& verticies, bool normalized = GL_FALSE);
        GLVertexBuffer(const std::vector<glm::vec3>& verticies, bool normalized = GL_FALSE);
        GLVertexBuffer(const std::vector<glm::vec4>& verticies, bool normalized = GL_FALSE);

        ~GLVertexBuffer();

        void Bind();
        void Unbind();

        int GetVerticiesCount() const;
        bool GetNormalized() const;

        GLuint GetId() const;

    private:
        template<class T>
        void CreateBuffer(const std::vector<T>& verticies, int verticiesCount);

        GLuint _bufferId;

        int _verticiesCount;
        bool _normalized;

    };

    class GLIndexBuffer
    {
    public:
        GLIndexBuffer(const std::vector<uint32_t>& indicies);
        ~GLIndexBuffer();

        void Bind();
        void Unbind();

        int GetIndiciesCount();

    private:
        GLuint _bufferId;

        int _indiciesCount;

    };
}

#endif
