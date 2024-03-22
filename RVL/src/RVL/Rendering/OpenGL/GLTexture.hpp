#pragma once

#include <Core/Core.hpp>
#include <Rvlpch.hpp>

namespace Rvl
{
    class GLTexture
    {
    public:
        GLTexture();
        GLTexture(u32 width, u32 height);
        GLTexture(const std::string& path);
        GLTexture(const GLTexture& tex) = delete;
        ~GLTexture();

        void LoadTexture(const std::string& path);
        void SetData(byte* data, i32 channels);

        void Bind(i32 unit) const;
        void Unbind(i32 unit) const;

        i32 GetWidth() const;
        i32 GetHeight() const;

        GLuint GetId() const;
        std::string GetPath() const;

        bool operator== (const GLTexture& tex) const;

    public:
        static GLuint TextureFromFile(const std::string& path, bool gamma = false);
        static void BindTextureUnit(GLuint texture, GLuint sampler, i32 unit);
        static void BindTextureUnit(GLuint texture, i32 unit);
        static void ActivateTexture(i32 unit);

    private:
        GLuint _textureId;
        GLenum _dataFormat, _internalFormat;
        
        i32 _width, _height, _channels;        

        std::string _path = "";
    };
}

