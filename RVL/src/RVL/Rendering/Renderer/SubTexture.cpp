#include "SubTexture.hpp"

namespace rvl
{
    Ref<SubTexture> SubTexture::Create(const Ref<GLTexture>& baseTexture, float x, float y, float spriteWidth, float spriteHeight)
    {
        Ref<SubTexture> texture = NewRef<SubTexture> ( baseTexture, x, y, spriteWidth, spriteHeight);

        return texture;
    }

    Ref<SubTexture> SubTexture::Create(const Ref<GLTexture>& baseTexture, const glm::vec2& pos, const glm::vec2& size)
    {
        return NewRef<SubTexture>(baseTexture, pos.x, pos.y, size.x, size.y);
    }

    SubTexture::SubTexture(const Ref<GLTexture>& baseTexture, float x, float y, float spriteWidth, float spriteHeight)
    {   
        _baseTexture = baseTexture;

        _x = x;
        _y = y;
        _width = spriteWidth;
        _height = spriteHeight;

        _min = glm::vec2((_x * _width) / _baseTexture->GetWidth(), (_y * _height) / _baseTexture->GetHeight());
        _max = glm::vec2(((_x + 1) * _width) / _baseTexture->GetWidth(), ((_y + 1) * _height) / _baseTexture->GetHeight());

        _textureCoords[0] = {_min.x, _min.y};
        _textureCoords[1] = {_max.x, _min.y};
        _textureCoords[2] = {_max.x, _max.y};
        _textureCoords[3] = {_min.x, _max.y};
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
