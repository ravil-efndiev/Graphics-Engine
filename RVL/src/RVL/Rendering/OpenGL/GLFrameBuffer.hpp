#pragma once

#include <Core/Core.hpp>

namespace Rvl
{
    struct FrameBufferSpecification
    {
        uint32 Width, Height;
        int Samples = 1;
    };

    class GLFrameBuffer
    {
    public:
        GLFrameBuffer(FrameBufferSpecification spec);
        ~GLFrameBuffer();

        GLuint GetColorAttachment();
        GLuint GetId();
        
        void Resize(float width, float height);
        void Resize(const glm::vec2& size);
        void Bind() const;
        void Blit(const Ref<GLFrameBuffer>& other) const;
        void Blit(GLuint other) const;
        void Unbind() const;

        float GetWidth() const;
        float GetHeight() const;

    private:
        GLuint _fboId;
        GLuint _colorAttachment;
        GLuint _rboId;

        float _width, _height;

        int _samples;
    };
}

