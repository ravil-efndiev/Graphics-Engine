#ifndef RVL_SUBTEXTURE_HPP
#define RVL_SUBTEXTURE_HPP

#include <Core/Core.hpp>
#include <Rendering/OpenGL/GLTexture.hpp>
#include <glm/glm.hpp>

namespace rvl
{
    class SubTexture
    {
    public:
        static Ref<SubTexture> CreateFromCoords(const Ref<GLTexture>& baseTexture, float x, float y, float spriteWidth, float spriteHeight);

        SubTexture(const Ref<GLTexture>& baseTexture, const glm::vec2& min, const glm::vec2& max);
        ~SubTexture();

        const glm::vec2* GetCoords() const;
        const Ref<GLTexture> GetTexture() const;

    private:
        Ref<GLTexture> _baseTexture;
        glm::vec2 _textureCoords[4];

    };
}

#endif
