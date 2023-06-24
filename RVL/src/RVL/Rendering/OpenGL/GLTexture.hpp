#pragma once

#include <Core/Core.hpp>
#include <Rvlpch.hpp>

namespace Rvl
{
    class GLTexture
    {
    public:
        GLTexture();
        GLTexture(uint32_t width, uint32_t height);
        GLTexture(const std::string& path);
        GLTexture(const GLTexture& tex) = delete;
        ~GLTexture();

        void LoadTexture(const std::string& path);
        void SetData(byte* data, int channels);

        void Bind(int unit) const;
        void Unbind() const;

        int GetWidth() const;
        int GetHeight() const;

        GLuint GetId() const;
        GLuint GetSamplerId() const;
        std::string GetPath() const;

        bool operator== (const GLTexture& tex) const;

    public:
        static GLuint TextureFromFile(const std::string& path, bool gamma = false);
        static void BindTextureUnit(GLuint texture, int unit);
        static void ActivateTexture(int unit);

    private:
        GLuint _textureId;
        GLuint _samplerId;
        GLenum _dataFormat;
        
        int _width, _height, _channels;        

        byte* _textureData;

        std::string _path = "";
    };
}

