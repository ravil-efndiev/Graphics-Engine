#include "SpriteComponent.hpp"

namespace Rvl
{
    SpriteComponent::SpriteComponent(const std::string& path, float scale)
    {
        _scale = scale;
        LoadTexture(path);
    }
    
    SpriteComponent::SpriteComponent(const Ref<GLTexture>& texture, float scale)
    {
        _scale = scale;
        LoadTexture(texture);
    }

    SpriteComponent::SpriteComponent(const glm::vec4& color)
    {
        _scale = 1.f;
        _color = color;
        _drawType = DrawType::Color;
        _fixedScale = false;
    }

    void SpriteComponent::LoadTexture(const std::string& path)
    {
        _drawType = DrawType::Texture;

        _texture = NewRef<GLTexture>(path);
        ResetScale();

        _subTexture = SubTexture::New(_texture, 0.f, 0.f, _texture->GetWidth(), _texture->GetHeight());
    }

    void SpriteComponent::LoadTexture(const Ref<GLTexture>& texture)
    {
        _drawType = DrawType::Texture;

        _texture = texture;
        ResetScale();

        _subTexture = SubTexture::New(_texture, 0.f, 0.f, _texture->GetWidth(), _texture->GetHeight());
    }

    void SpriteComponent::SetSubTexture(float x, float y, float spriteWidth, float spriteHeight)
    {
        RVL_ASSERT((_drawType == DrawType::Texture), "Cannot load subtexture into sprite without base texture");
        _subTexture = SubTexture::New(_texture, x, y, spriteWidth, spriteHeight);

        if (_fixedScale)
        {
            float ratio = spriteWidth / spriteHeight;
            _currentScale = glm::vec2(ratio * _scale, _scale);
        }
    }

    void SpriteComponent::SetSubTexture(const Ref<SubTexture>& subTexture)
    {
        RVL_ASSERT((_drawType == DrawType::Texture), "Cannot load subtexture into sprite without base texture");
        _subTexture = SubTexture::New(_texture, subTexture->GetX(), subTexture->GetY(), subTexture->GetWidth(), subTexture->GetHeight());

        if (_fixedScale)
        {
            float ratio = subTexture->GetWidth() / subTexture->GetHeight();
            _currentScale = glm::vec2(ratio * _scale, _scale);
        }
    }

    void SpriteComponent::ResetScale()
    {
        RVL_ASSERT((_drawType == DrawType::Texture), "Cannot reset scale based on texture in sprite without texture");
        float ratio = (float)_texture->GetWidth() / (float)_texture->GetHeight();

        _currentScale = glm::vec2(ratio * _scale, _scale);
    }

    void SpriteComponent::ResetSubTexture()
    {
        RVL_ASSERT((_drawType == DrawType::Texture), "Cannot reset subtexture in sprite without texture");

        if (_fixedScale)            
            ResetScale();

        _subTexture = SubTexture::New(_texture, 0.f, 0.f, _texture->GetWidth(), _texture->GetHeight());
    }  

    Ref<GLTexture> SpriteComponent::GetTexture() const
    {
        return _texture;
    }

    Ref<SubTexture> SpriteComponent::GetSubTexture() const
    {
        return _subTexture;
    }
    
    void SpriteComponent::SetColor(const glm::vec4& color)
    {
        _color = color;
    }

    glm::vec4 SpriteComponent::GetColor() const
    {
        return _color;
    }
    
    SpriteComponent::DrawType SpriteComponent::GetDrawType() const
    {
        return _drawType;
    }
    
    void SpriteComponent::UseColorAsTint(bool flag)
    {
        _useColorAsTint = flag;
    }

    bool SpriteComponent::ColorIsTint() const
    {
        return _useColorAsTint;
    }
    
    glm::vec2 SpriteComponent::GetCurrentScale() const
    {
        return _currentScale;
    }
    
    bool SpriteComponent::GetFixedScale() const
    {
        return _fixedScale;
    }
    
    void SpriteComponent::SetFixedScale(bool flag)
    {
        _fixedScale = flag;
    }
}
