#include "GLTexture.hpp"

#include <Rvlglpch.hpp>
#include <stb_image.h>

#include <Core/Core.hpp>

namespace rvl
{
    GLTexture::GLTexture() {}

    GLTexture::GLTexture(uint32_t width, uint32_t height)
    {
        _width = width;
        _height = height;

        glGenTextures(1, &_textureId);
        glBindTexture(GL_TEXTURE_2D, _textureId);

        GLenum dataFormat;
        dataFormat = _channels == 4 ? GL_RGBA : GL_RGB;

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

        glTexImage2D(GL_TEXTURE_2D, 0, dataFormat, _width, _height, 0, dataFormat, GL_UNSIGNED_BYTE, nullptr);
        glGenerateMipmap(GL_TEXTURE_2D);
    }

    GLTexture::GLTexture(const std::string &path)
    {       
        LoadTexture(path);
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

    void GLTexture::SetData(uint8_t* data, size_t size)
    {
        glBindTexture(GL_TEXTURE_2D, _textureId);
        _textureData = data;
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, _width, _height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    }

    void GLTexture::Bind() const
    {
        glActiveTexture(GL_TEXTURE0);
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
}
