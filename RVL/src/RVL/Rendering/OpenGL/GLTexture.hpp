#ifndef RVL_GLTEXTURE_HPP
#define RVL_GLTEXTURE_HPP

#include <Rvlpch.hpp>

namespace rvl
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
        void SetData(uint8_t* data, int channels);

        void Bind(int unit) const;
        void Unbind() const;

        int GetWidth() const;
        int GetHeight() const;

        GLuint GetId() const;
        std::string GetPath() const;

        bool operator== (const GLTexture& tex) const;

    private:
        GLuint _textureId;
        GLuint _samplerId;
        GLenum _dataFormat;
        int _width, _height, _channels;        
        unsigned char* _textureData;

        std::string _path = "";
    };
}

#endif
