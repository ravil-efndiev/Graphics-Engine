#include "SubTexture.hpp"

namespace rvl
{
    Ref<SubTexture> SubTexture::CreateFromCoords(const Ref<GLTexture>& baseTexture, float x, float y, float spriteWidth, float spriteHeight)
    {
        Ref<SubTexture> texture = NewRef<SubTexture> (
            baseTexture,
            glm::vec2((x * spriteWidth) / baseTexture->GetWidth(), (y * spriteHeight) / baseTexture->GetHeight()),
            glm::vec2(((x + 1) * spriteWidth) / baseTexture->GetWidth(), ((y + 1) * spriteHeight) / baseTexture->GetHeight())
        );

        return texture;
    }

    SubTexture::SubTexture(const Ref<GLTexture>& baseTexture, const glm::vec2& min, const glm::vec2& max)
    {   
        _baseTexture = baseTexture;

        _textureCoords[0] = {min.x, min.y};
        _textureCoords[1] = {max.x, min.y};
        _textureCoords[2] = {max.x, max.y};
        _textureCoords[3] = {min.x, max.y};
    }

    SubTexture::~SubTexture() {}

    const glm::vec2* SubTexture::GetCoords() const
    {
        return _textureCoords;
    }
    
    const Ref<GLTexture> SubTexture::GetTexture() const
    {
        return _baseTexture;
    }
}
