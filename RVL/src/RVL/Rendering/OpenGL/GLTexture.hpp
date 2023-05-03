#ifndef RVL_GLTEXTURE_HPP
#define RVL_GLTEXTURE_HPP

#include <Rvlpch.hpp>

namespace rvl
{
    class GLTexture
    {
    public:
        GLTexture();
        GLTexture(const std::string& path);
        GLTexture(const GLTexture& tex) = delete;
        ~GLTexture();

        void LoadTexture(const std::string& path);

        void Bind() const;
        void Unbind() const;

        int GetWidth() const;
        int GetHeight() const;

        int GetUnit() const;

    private:
        GLuint _textureId;
        int _width, _height, _channels;        
        unsigned char* _textureData;

        static int s_Unit;
        int m_Unit;

    };
}

#endif
