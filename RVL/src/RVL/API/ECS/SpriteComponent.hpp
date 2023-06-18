#pragma once

#include "Entity.hpp"
#include "TransformComponent.hpp"
#include <Rendering/Renderer/SubTexture.hpp>
#include <Rendering/OpenGL/GLTexture.hpp>

namespace Rvl
{
    class SpriteComponent : public Component
    {
    public:
        SpriteComponent() = default;
        SpriteComponent(const SpriteComponent&) = default;
        SpriteComponent(Entity* self, const std::string& path, float scale);
        SpriteComponent(Entity* self, const Ref<GLTexture>& texture, float scale);
        SpriteComponent(Entity* self, const glm::vec4& color);

        enum class DrawType { Color, Texture };

        void LoadTexture(const std::string& path);
        void LoadTexture(const Ref<GLTexture>& texture);
        
        void SetSubTexture(float x, float y, float spriteWidth, float spriteHeight);
        void SetSubTexture(const Ref<SubTexture>& subTexture);
        
        void ResetScale();
        void ResetSubTexture();

        Ref<GLTexture> GetTexture() const;
        Ref<SubTexture> GetSubTexture() const;

        void SetColor(const glm::vec4& color);
        glm::vec4 GetColor() const;

        DrawType GetDrawType() const;

        void UseColorAsTint(bool flag);
        bool ColorIsTint() const;

    private:
        float _scale;

        Ref<SubTexture> _subTexture;
        Ref<GLTexture> _texture;
        glm::vec4 _color;

        DrawType _drawType;

        bool _useColorAsTint;
    };
}

