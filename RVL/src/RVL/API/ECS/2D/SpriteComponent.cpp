#include "SpriteComponent.hpp"

namespace Rvl
{
    SpriteComponent::SpriteComponent()
    {
        Scale = 1.f;
        Color = {1.f, 1.f, 1.f, 1.f};
        Drawtype = DrawType::Color;
        UseFixedScale = false;
    }

    SpriteComponent::SpriteComponent(const std::string& path, float scale)
    {
        Scale = scale;
        LoadTexture(path);
    }
    
    SpriteComponent::SpriteComponent(const Ref<GLTexture>& texture, float scale)
    {
        Scale = scale;
        LoadTexture(texture);
    }

    SpriteComponent::SpriteComponent(const glm::vec4& color)
    {
        Scale = 1.f;
        Color = color;
        Drawtype = DrawType::Color;
        UseFixedScale = false;
    }

    void SpriteComponent::LoadTexture(const std::string& path)
    {
        Drawtype = DrawType::Texture;

        Texture = NewRef<GLTexture>(path);

        SetSubTexture(0.f, 0.f, Texture->GetWidth(), Texture->GetHeight());
    }

    void SpriteComponent::LoadTexture(const Ref<GLTexture>& texture)
    {
        Drawtype = DrawType::Texture;

        Texture = texture;

        SetSubTexture(0.f, 0.f, Texture->GetWidth(), Texture->GetHeight());
    }

    void SpriteComponent::SetSubTexture(float x, float y, float spriteWidth, float spriteHeight)
    {
        RVL_ASSERT((Drawtype == DrawType::Texture), "Cannot load subtexture into sprite without base texture");
        Subtexture = SubTexture::New(Texture, x, y, spriteWidth, spriteHeight);

        if (UseFixedScale)
        {
            float ratio = spriteWidth / spriteHeight;
            ScaleVec2 = glm::vec2(ratio * Scale, Scale);
        }
    }

    void SpriteComponent::SetSubTexture(const Ref<SubTexture>& subTexture)
    {
        RVL_ASSERT((Drawtype == DrawType::Texture), "Cannot load subtexture into sprite without base texture");
        Subtexture = SubTexture::New(Texture, subTexture->GetX(), subTexture->GetY(), subTexture->GetWidth(), subTexture->GetHeight());

        if (UseFixedScale)
        {
            float ratio = subTexture->GetWidth() / subTexture->GetHeight();
            ScaleVec2 = glm::vec2(ratio * Scale, Scale);
        }
    }

    void SpriteComponent::ResetScale()
    {
        RVL_ASSERT((Drawtype == DrawType::Texture), "Cannot reset scale based on texture in sprite without texture");
        float ratio = (float)Texture->GetWidth() / (float)Texture->GetHeight();

        ScaleVec2 = glm::vec2(ratio * Scale, Scale);
    }

    void SpriteComponent::ResetSubTexture()
    {
        RVL_ASSERT((Drawtype == DrawType::Texture), "Cannot reset subtexture in sprite without texture");

        if (UseFixedScale)            
            ResetScale();

        Subtexture = SubTexture::New(Texture, 0.f, 0.f, Texture->GetWidth(), Texture->GetHeight());
    }  

}
