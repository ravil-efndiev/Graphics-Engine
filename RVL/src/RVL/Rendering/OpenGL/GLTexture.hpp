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
        ~GLTexture();

        void LoadTexture(const std::string& path);

        void Bind(int unit);
        void Unbind();

        int GetWidth() const;
        int GetHeight() const;

    private:
        GLuint _textureId;
        int _width, _height, _channels;        
        unsigned char* _textureData;

    };
}

#endif
