#pragma once

#include <Rendering/Renderer/SubTexture.hpp>
#include <Rendering/OpenGL/GLTexture.hpp>
#include <Entity.hpp>

namespace Rvl
{
    class SpriteComponent
    {
    public:
        SpriteComponent() = default;
        SpriteComponent(const SpriteComponent&) = default;
        SpriteComponent(const std::string& path, float scale);
        SpriteComponent(const Ref<GLTexture>& texture, float scale);
        SpriteComponent(const glm::vec4& color);

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

        glm::vec2 GetCurrentScale() const;

        bool GetFixedScale() const;
        void SetFixedScale(bool flag);

        friend class InspectorWindow;
    private:
        float _scale;

        Ref<SubTexture> _subTexture;
        Ref<GLTexture> _texture;
        DrawType _drawType;

        glm::vec4 _color { 1.f };
        glm::vec2 _currentScale { 0.f };

        bool _useColorAsTint;
        bool _fixedScale = true;
    };
}

