#pragma once

#include <Core/Core.hpp>
#include <Rendering/OpenGL/GLTexture.hpp>
#include <glm/glm.hpp>

namespace Rvl
{
    class SubTexture
    {
    public:
        static Ref<SubTexture> New(const Ref<GLTexture>& baseTexture, float x, float y, float spriteWidth, float spriteHeight);
        static Ref<SubTexture> New(const Ref<GLTexture>& baseTexture, const glm::vec2& pos, const glm::vec2& size);

        SubTexture(const Ref<GLTexture>& baseTexture, float x, float y, float spriteWidth, float spriteHeight);
        ~SubTexture();

        const glm::vec2* GetCoords() const;
        const Ref<GLTexture> GetTexture() const;

        glm::vec2 GetMin() const { return _min; }
        glm::vec2 GetMax() const { return _max; }

        float GetX() const { return _x; }
        float GetY() const { return _y; }
        float GetWidth() const { return _width; }
        float GetHeight() const { return _height; }

    private:
        Ref<GLTexture> _baseTexture;
        glm::vec2 _textureCoords[4];

        glm::vec2 _min, _max;

        float _x, _y, _width, _height;
    };
}

