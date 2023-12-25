#include "Sprite.hpp"

namespace Rvl
{
    Sprite::Sprite()
    {
        UseTexture = false;
        FixedScale = 1.f;
        Color = {1.f, 1.f, 1.f, 1.f};
    }

    Sprite::Sprite(const std::string& path, float scale)
    {
        FixedScale = scale;
        LoadTexture(path);
    }
    
    Sprite::Sprite(const Ref<GLTexture>& texture, float scale)
    {
        FixedScale = scale;
        LoadTexture(texture);
    }

    Sprite::Sprite(const glm::vec4& color)
    {
        UseTexture = false;
        FixedScale = 1.f;
        Color = color;
        UseFixedScale = false;
    }

    void Sprite::LoadTexture(const std::string& path)
    {
        Texture = NewRef<GLTexture>(path);

        UseTexture = false;

        SetSubTexture(0.f, 0.f, Texture->GetWidth(), Texture->GetHeight());
    }

    void Sprite::LoadTexture(const Ref<GLTexture>& texture)
    {
        Texture = texture;

        UseTexture = false;

        SetSubTexture(0.f, 0.f, Texture->GetWidth(), Texture->GetHeight());
    }

    void Sprite::SetSubTexture(float x, float y, float spriteWidth, float spriteHeight)
    {
        if (!Texture) return;
        Subtexture = SubTexture::New(Texture, x, y, spriteWidth, spriteHeight);
    }

    void Sprite::SetSubTexture(const Ref<SubTexture>& subTexture)
    {
        if (!Texture) return;
        Subtexture = SubTexture::New(Texture, subTexture->GetX(), subTexture->GetY(), subTexture->GetWidth(), subTexture->GetHeight());
    }

    void Sprite::ResetSubTexture()
    {
        if (!Texture) return;

        Subtexture = SubTexture::New(Texture, 0.f, 0.f, Texture->GetWidth(), Texture->GetHeight());
    }  

}
