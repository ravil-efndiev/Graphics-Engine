#include "GLFrameBuffer.hpp"

#include <Rvlglpch.hpp>

namespace Rvl
{
    GLFrameBuffer::GLFrameBuffer(FrameBufferSpecification spec)
        : _width(spec.Width), _height(spec.Height), _samples(spec.Samples)
    {
        glGenFramebuffers(1, &_fboId);
        glBindFramebuffer(GL_FRAMEBUFFER, _fboId);

        if (_samples > 1)
        {
            glGenTextures(1, &_colorAttachment);
            glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, _colorAttachment);
            glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, _samples, GL_RGB, _width, _height, GL_TRUE);
            glTexParameteri(GL_TEXTURE_2D_MULTISAMPLE, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D_MULTISAMPLE, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D_MULTISAMPLE, _colorAttachment, 0);

            glGenRenderbuffers(1, &_rboId);
            glBindRenderbuffer(GL_RENDERBUFFER, _rboId);
            glRenderbufferStorageMultisample(GL_RENDERBUFFER, _samples, GL_DEPTH24_STENCIL8, _width, _height);
            glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, _rboId);

            RVL_ASSERT((glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE), "Frame buffer is not complete");

            glBindFramebuffer(GL_FRAMEBUFFER, 0);
            glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, 0);
            glBindRenderbuffer(GL_RENDERBUFFER, 0);
        }
        else
        {
            glGenTextures(1, &_colorAttachment);
            glBindTexture(GL_TEXTURE_2D, _colorAttachment);
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, _width, _height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, _colorAttachment, 0);

            glGenRenderbuffers(1, &_rboId);
            glBindRenderbuffer(GL_RENDERBUFFER, _rboId);
            glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, _width, _height);
            glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, _rboId);

            RVL_ASSERT((glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE), "Frame buffer is not complete");

            glBindFramebuffer(GL_FRAMEBUFFER, 0);
            glBindTexture(GL_TEXTURE_2D, 0);
            glBindRenderbuffer(GL_RENDERBUFFER, 0);
        }
    }

    GLFrameBuffer::~GLFrameBuffer()
    {
        glDeleteFramebuffers(1, &_fboId);
        glDeleteTextures(1, &_colorAttachment);
        glDeleteRenderbuffers(1, &_rboId);
    }

    unsigned int GLFrameBuffer::GetColorAttachment()
    {
        return _colorAttachment;
    }

    void GLFrameBuffer::Resize(float width, float height)
    {
        _width = width;
        _height = height;

        glViewport(0, 0, width, height);

        if (_samples > 1)
        {
            glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, _colorAttachment);
            glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, _samples, GL_RGB, width, height, GL_TRUE);
            glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D_MULTISAMPLE, _colorAttachment, 0);

            glBindRenderbuffer(GL_RENDERBUFFER, _rboId);
            glRenderbufferStorageMultisample(GL_RENDERBUFFER, _samples, GL_DEPTH24_STENCIL8, width, height);
            glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, _rboId);
        }
        else
        {
            glBindTexture(GL_TEXTURE_2D, _colorAttachment);
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, _width, _height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
            glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, _colorAttachment, 0);

            glBindRenderbuffer(GL_RENDERBUFFER, _rboId);
            glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);
            glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, _rboId);
        }
    }

    void GLFrameBuffer::Resize(const glm::vec2& size)
    {
        Resize(size.x, size.y);
    }

    void GLFrameBuffer::Bind() const
    {
        glBindFramebuffer(GL_FRAMEBUFFER, _fboId);
    }

    void GLFrameBuffer::Blit(const Ref<GLFrameBuffer>& other) const
    {
        Blit(other->_fboId);
    }

    void GLFrameBuffer::Blit(GLuint other) const
    {
        glBindFramebuffer(GL_READ_FRAMEBUFFER, _fboId);
        glBindFramebuffer(GL_DRAW_FRAMEBUFFER, other);
        glBlitFramebuffer(0, 0, _width, _height, 0, 0, _width, _height, GL_COLOR_BUFFER_BIT, GL_NEAREST); 
    }

    void GLFrameBuffer::Unbind() const
    {
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }
    
    float GLFrameBuffer::GetWidth() const
    {
        return _width;
    }

    float GLFrameBuffer::GetHeight() const
    {
        return _height;
    }

    GLuint GLFrameBuffer::GetId()
    {
        return _fboId;
    }

}
