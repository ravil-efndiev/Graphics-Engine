#pragma once

#include <Rvlglpch.hpp>
#include <Core/Core.hpp>

namespace Rvl
{
    enum class ElementType
    {
        Float = 1,
        Vec2  = 2,
        Vec3  = 3,
        Vec4  = 4,
    };
    
    struct LayoutElement
    {
        ElementType Type = ElementType::Float;
        
        uint64 Offset = 0;
        uint32 Size = (int32)Type * sizeof(float);

        bool Normalized = false;
    };

    class GLVertexBuffer
    {
    public:
        GLVertexBuffer(size_t size, int components, bool normalized = GL_FALSE);

        template <class T>
        GLVertexBuffer(const std::vector<T>& verticies)
        {
            glGenBuffers(1, &_bufferId);
            glBindBuffer(GL_ARRAY_BUFFER, _bufferId);
            glBufferData(GL_ARRAY_BUFFER, verticies.size() * sizeof(T), verticies.data(), GL_STATIC_DRAW);   
        }

  
        GLVertexBuffer(const std::vector<float>& verticies, bool normalized = GL_FALSE);
        GLVertexBuffer(const std::vector<glm::vec2>& verticies, bool normalized = GL_FALSE);
        GLVertexBuffer(const std::vector<glm::vec3>& verticies, bool normalized = GL_FALSE);
        GLVertexBuffer(const std::vector<glm::vec4>& verticies, bool normalized = GL_FALSE);

        ~GLVertexBuffer();

        void Bind();
        void Unbind();

        void SetData(void* data, size_t size);

        int GetVerticiesCount() const;
        bool GetNormalized() const;

        GLuint GetId() const;

        void SetLayout(const std::initializer_list<LayoutElement>& layout);
        std::vector<LayoutElement> GetLayout() const;

        bool IsLayoutUsed() const;

    private:
        template<class T>
        void CreateBuffer(const std::vector<T>& verticies, int verticiesCount);
        void CreateBuffer(size_t size);

        GLuint _bufferId;

        int _verticiesCount;
        bool _normalized;

        std::vector<LayoutElement> _layout;
    };
}
