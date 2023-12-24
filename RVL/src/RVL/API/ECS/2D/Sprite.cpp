#include "Sprite.hpp"

namespace Rvl
{
    Sprite::Sprite()
    {
        Scale = 1.f;
        Color = {1.f, 1.f, 1.f, 1.f};
        Drawtype = DrawType::Color;
        UseFixedScale = false;
    }

    Sprite::Sprite(const std::string& path, float scale)
    {
        Scale = scale;
        LoadTexture(path);
    }
    
    Sprite::Sprite(const Ref<GLTexture>& texture, float scale)
    {
        Scale = scale;
        LoadTexture(texture);
    }

    Sprite::Sprite(const glm::vec4& color)
    {
        Scale = 1.f;
        Color = color;
        Drawtype = DrawType::Color;
        UseFixedScale = false;
    }

    void Sprite::LoadTexture(const std::string& path)
    {
        Drawtype = DrawType::Texture;

        Texture = NewRef<GLTexture>(path);

        SetSubTexture(0.f, 0.f, Texture->GetWidth(), Texture->GetHeight());
    }

    void Sprite::LoadTexture(const Ref<GLTexture>& texture)
    {
        Drawtype = DrawType::Texture;

        Texture = texture;

        SetSubTexture(0.f, 0.f, Texture->GetWidth(), Texture->GetHeight());
    }

    void Sprite::SetSubTexture(float x, float y, float spriteWidth, float spriteHeight)
    {
        RVL_ASSERT((Drawtype == DrawType::Texture), "Cannot load subtexture into sprite without base texture");
        Subtexture = SubTexture::New(Texture, x, y, spriteWidth, spriteHeight);

        float ratio = spriteWidth / spriteHeight;
        ScaleVec2 = glm::vec2(ratio * Scale, Scale);
    }

    void Sprite::SetSubTexture(const Ref<SubTexture>& subTexture)
    {
        RVL_ASSERT((Drawtype == DrawType::Texture), "Cannot load subtexture into sprite without base texture");
        Subtexture = SubTexture::New(Texture, subTexture->GetX(), subTexture->GetY(), subTexture->GetWidth(), subTexture->GetHeight());

        float ratio = subTexture->GetWidth() / subTexture->GetHeight();
        ScaleVec2 = glm::vec2(ratio * Scale, Scale);
    }

    void Sprite::ResetScale()
    {
        RVL_ASSERT((Drawtype == DrawType::Texture), "Cannot reset scale based on texture in sprite without texture");
        float ratio = (float)Texture->GetWidth() / (float)Texture->GetHeight();

        ScaleVec2 = glm::vec2(ratio * Scale, Scale);
    }

    void Sprite::ResetSubTexture()
    {
        RVL_ASSERT((Drawtype == DrawType::Texture), "Cannot reset subtexture in sprite without texture");

        ResetScale();

        Subtexture = SubTexture::New(Texture, 0.f, 0.f, Texture->GetWidth(), Texture->GetHeight());
    }  

}
