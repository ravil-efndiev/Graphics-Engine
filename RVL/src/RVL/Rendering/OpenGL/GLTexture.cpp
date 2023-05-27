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

        glGenSamplers(1, &_samplerId);

        glSamplerParameteri(_samplerId, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glSamplerParameteri(_samplerId, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glSamplerParameteri(_samplerId, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glSamplerParameteri(_samplerId, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

        _dataFormat = GL_RGB;

        glTexImage2D(GL_TEXTURE_2D, 0, _dataFormat, _width, _height, 0, _dataFormat, GL_UNSIGNED_BYTE, nullptr);
        glGenerateMipmap(GL_TEXTURE_2D);

        glBindTexture(GL_TEXTURE_2D, 0);
    }

    GLTexture::GLTexture(const std::string &path)
    {       
        LoadTexture(path);
        _path = path;
    }

    GLTexture::~GLTexture() 
    {
        glDeleteTextures(1, &_textureId);
        glDeleteSamplers(1, &_samplerId);
    }

    void GLTexture::LoadTexture(const std::string& path)
    {
        stbi_set_flip_vertically_on_load(true);

        _textureData = stbi_load(path.c_str(), &_width, &_height, &_channels, 0);
        if (!_textureData)
        {
            throw Error("Failed to load texture", RVL_RUNTIME_ERROR);
        }

        glGenTextures(1, &_textureId);
        glBindTexture(GL_TEXTURE_2D, _textureId);

        _dataFormat = _channels == 4 ? GL_RGBA : GL_RGB;

        glGenSamplers(1, &_samplerId);

        glSamplerParameteri(_samplerId, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glSamplerParameteri(_samplerId, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glSamplerParameteri(_samplerId, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glSamplerParameteri(_samplerId, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

        glTexImage2D(GL_TEXTURE_2D, 0, _dataFormat, _width, _height, 0, _dataFormat, GL_UNSIGNED_BYTE, _textureData);
        glGenerateMipmap(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, 0);

        stbi_image_free(_textureData);
    }

    void GLTexture::SetData(uint8_t* data, int channels)
    {
        RVL_ASSERT((channels == 4 || channels == 3), "number of channels in texture can be only 4 or 3");

        _channels = channels;
        _dataFormat = _channels == 4 ? GL_RGBA : GL_RGB;
        _textureData = data;

        glBindTexture(GL_TEXTURE_2D, _textureId);
        glTexImage2D(GL_TEXTURE_2D, 0, _dataFormat, _width, _height, 0, _dataFormat, GL_UNSIGNED_BYTE, data);
        glBindTexture(GL_TEXTURE_2D, 0);
    }

    void GLTexture::Bind(int unit) const
    {
        glActiveTexture(GL_TEXTURE0 + unit);
        glBindTexture(GL_TEXTURE_2D, _textureId);
        glBindSampler(unit, _samplerId);
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

    GLuint GLTexture::GetId() const
    {
        return _textureId;
    }

    bool GLTexture::operator==(const GLTexture& tex) const
    {
        return _path == "" ? _textureId == tex._textureId : _path == tex._path;
    }

    std::string GLTexture::GetPath() const
    {
        return _path;
    }

}
