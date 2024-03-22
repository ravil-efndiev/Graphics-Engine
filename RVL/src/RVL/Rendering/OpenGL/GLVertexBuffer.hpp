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
        Mat4  = 16,
    };
    
    struct LayoutElement
    {
        ElementType Type = ElementType::Float;
        
        u64 Offset = 0;
        u32 Size = (i32)Type * sizeof(f32);

        bool Normalized = false;
    };

    class GLVertexBuffer
    {
    public:
        GLVertexBuffer();
        GLVertexBuffer(size_t size, i32 components = 0, bool normalized = GL_FALSE);

        template <class T>
        GLVertexBuffer(const std::vector<T>& verticies, bool dynamic = false)
        {
            glGenBuffers(1, &_bufferId);
            glBindBuffer(GL_ARRAY_BUFFER, _bufferId);
            glBufferData(GL_ARRAY_BUFFER, verticies.size() * sizeof(T), verticies.data(), dynamic ? GL_DYNAMIC_DRAW : GL_STATIC_DRAW);   
        }

        ~GLVertexBuffer();

        void Bind();
        void Unbind();

        void SetData(void* data, size_t size);
        void ReallocData(void* data, size_t size);

        i32 GetVerticiesCount() const;
        bool GetNormalized() const;

        GLuint GetId() const;

        void SetLayout(const std::initializer_list<LayoutElement>& layout);
        std::vector<LayoutElement> GetLayout() const;

        bool IsLayoutUsed() const;

    private:
        template<class T>
        void CreateBuffer(const std::vector<T>& verticies, i32 verticiesCount);
        void CreateBuffer(size_t size);

        GLuint _bufferId;

        i32 _verticiesCount;
        bool _normalized;

        std::vector<LayoutElement> _layout;
    };
}
