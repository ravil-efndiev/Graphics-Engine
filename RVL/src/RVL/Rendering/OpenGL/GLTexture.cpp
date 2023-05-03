#include "GLTexture.hpp"

#include <Rvlglpch.hpp>
#include <stb_image.h>

#include <Core/Core.hpp>

namespace rvl
{
    int GLTexture::s_Unit = 0;

    GLTexture::GLTexture() {}

    GLTexture::GLTexture(const std::string &path)
    {       
        m_Unit = s_Unit;
        RVL_LOG(s_Unit << " " << m_Unit);
        LoadTexture(path);
        s_Unit++;
    }

    GLTexture::~GLTexture() 
    {
        glDeleteTextures(1, &_textureId);
    }

    void GLTexture::LoadTexture(const std::string &path)
    {
        stbi_set_flip_vertically_on_load(true);

        _textureData = stbi_load(path.c_str(), &_width, &_height, &_channels, 0);
        if (!_textureData)
        {
            throw Error("Failed to load texture", RVL_RUNTIME_ERROR);
        }

        glGenTextures(1, &_textureId);
        glBindTexture(GL_TEXTURE_2D, _textureId);

        GLenum dataFormat;
        dataFormat = _channels == 4 ? GL_RGBA : GL_RGB;

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

        glTexImage2D(GL_TEXTURE_2D, 0, dataFormat, _width, _height, 0, dataFormat, GL_UNSIGNED_BYTE, _textureData);
        glGenerateMipmap(GL_TEXTURE_2D);
        stbi_image_free(_textureData);
    }

    void GLTexture::Bind() const
    {
        glActiveTexture(GL_TEXTURE0 + m_Unit);
        glBindTexture(GL_TEXTURE_2D, _textureId);
    }

    void GLTexture::Unbind() const
    {
        glBindTexture(GL_TEXTURE_2D, 0);
    }

    int GLTexture::GetWidth() const
    {
        return _width;
    }

    int GLTexture::GetHeight() const
    {
        return _height;
    }
    
    int GLTexture::GetUnit() const
    {
        return m_Unit;
    }
}
