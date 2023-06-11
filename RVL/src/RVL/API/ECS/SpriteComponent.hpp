#ifndef RVL_SPRITECOMPONENT_HPP
#define RVL_SPRITECOMPONENT_HPP

#include "Entity.hpp"
#include "TransformComponent.hpp"
#include <Rendering/Renderer/SubTexture.hpp>
#include <Rendering/OpenGL/GLTexture.hpp>

namespace Rvl
{
    class SpriteComponent
    {
    public:
        SpriteComponent() = default;
        SpriteComponent(const SpriteComponent&) = default;
        SpriteComponent(Entity* target, const std::string& path, float scale);
        SpriteComponent(Entity* target, const Ref<GLTexture>& texture, float scale);
        SpriteComponent(Entity* target, const glm::vec4& color);

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
        Entity* _target;

        float _scale;

        Ref<SubTexture> _subTexture;
        Ref<GLTexture> _texture;
        glm::vec4 _color;

        DrawType _drawType;

        bool _useColorAsTint;
    };
}

#endif
