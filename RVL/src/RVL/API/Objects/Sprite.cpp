#include "Sprite.hpp"
#include <Rvlglpch.hpp>

#include <stb_image.h>
#include <Core/Core.hpp>

#include "Rendering/OpenGL/GLShaderProgram.hpp"
#include "Rendering/OpenGL/GLVertexArray.hpp"
#include "Rendering/OpenGL/GLBuffer.hpp"
#include "Rendering/OpenGL/GLTexture.hpp"

#include "Rendering/Renderer/Renderer.hpp"

namespace rvl
{
    Ref<Sprite> Sprite::Create()
    {
        return NewRef<Sprite>();
    }

    Ref<Sprite> Sprite::Create(const glm::vec3& position, float scale)
    {
        return NewRef<Sprite>(position, scale);
    }

    Sprite::Sprite() : Entity() {}

    Sprite::Sprite(const glm::vec3& position, float scale) : Entity(Transform(position, 0.f, {0.f, 0.f}))
    {
        _scale = scale;
    }

    Sprite::~Sprite() {}

    void Sprite::LoadTexture(const std::string& path)
    {
        _texture = NewRef<GLTexture>(path);   

        ResetScale();

        _subTexture = SubTexture::Create(_texture, 0.f, 0.f, _texture->GetWidth(), _texture->GetHeight());
    }

    void Sprite::LoadTexture(const Ref<GLTexture>& texture)
    {
        _texture = texture;
        ResetScale();

        _subTexture = SubTexture::Create(_texture, 0.f, 0.f, _texture->GetWidth(), _texture->GetHeight());
    }

    void Sprite::SetSubTexture(float x, float y, float spriteWidth, float spriteHeight)
    {
        _subTexture = SubTexture::Create(_texture, x, y, spriteWidth, spriteHeight);

        float ratio = spriteWidth / spriteHeight;
        _transform.Scale = glm::vec2(ratio * _scale, _scale);
    }

    void Sprite::SetSubTexture(const Ref<SubTexture>& subTexture)
    {
        _subTexture = SubTexture::Create(_texture, subTexture->GetX(), subTexture->GetY(), subTexture->GetWidth(), subTexture->GetHeight());

        float ratio = subTexture->GetWidth() / subTexture->GetHeight();
        _transform.Scale = glm::vec2(ratio * _scale, _scale);
    }

    void Sprite::ResetScale()
    {
        float ratio = (float)_texture->GetWidth() / (float)_texture->GetHeight();

        _transform.Scale = glm::vec2(ratio * _scale, _scale);
    }

    void Sprite::ResetSubTexture()
    {
        ResetScale();
        _subTexture = SubTexture::Create(_texture, 0.f, 0.f, _texture->GetWidth(), _texture->GetHeight());
    }  

    void Sprite::Draw()
    {
        Transform tf = {
            _hasParent ? _realPosition : _transform.Position,
            _hasParent ? _realRotationZ : _transform.Rotation,
            _transform.Scale
        };
        Renderer::DrawRect(tf, _subTexture);
    }

    void Sprite::Draw(const glm::vec4& tintColor)
    {
        Transform tf = {
            _hasParent ? _realPosition : _transform.Position,
            _hasParent ? _realRotationZ : _transform.Rotation,
            _transform.Scale
        };
        Renderer::DrawRect(tf, _subTexture, tintColor);   
    }

    Ref<GLTexture> Sprite::GetTexture() const
    {
        return _texture;
    }

}
