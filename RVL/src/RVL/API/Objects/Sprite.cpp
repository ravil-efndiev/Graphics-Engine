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
        return CreateRef<Sprite>();
    }

    Ref<Sprite> Sprite::Create(const glm::vec3& position, float scale)
    {
        return CreateRef<Sprite>(position, scale);
    }

    Sprite::Sprite() : Entity() {}

    Sprite::Sprite(const glm::vec3& position, float scale) : Entity(Transform(position, 0.f, {0.f, 0.f}))
    {
        _scale = scale;
    }

    Sprite::~Sprite() {}

    void Sprite::LoadTexture(const std::string& path)
    {
        _texture = CreateRef<GLTexture>(path);   

        ResetScale();
    }

    void Sprite::ResetScale()
    {
        float ratio = (float)_texture->GetWidth() / (float)_texture->GetHeight();

        _transform.Scale = glm::vec2(ratio * _scale, _scale);
    }

    void Sprite::Draw()
    {
        Renderer::DrawRect(_transform, *_texture);
    }

    Ref<GLTexture> Sprite::GetTexture() const
    {
        return _texture;
    }

}
