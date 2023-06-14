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
        GLFrameBuffer(float width, float height);
        ~GLFrameBuffer();

        GLuint GetColorAttachment();
        
        void RescaleFrameBuffer(float width, float height);
        void Bind() const;
        void Unbind() const;

        float GetWidth() const;
        float GetHeight() const;

    private:
        GLuint _fboId;
        GLuint _colorAttachment;
        GLuint _rboId;

        float _width, _height;
    };
}

