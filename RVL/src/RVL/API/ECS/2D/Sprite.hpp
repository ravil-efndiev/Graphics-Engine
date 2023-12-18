#pragma once

#include <Rendering/Renderer/SubTexture.hpp>
#include <Rendering/OpenGL/GLTexture.hpp>
#include <Entity.hpp>

namespace Rvl
{
    struct Sprite
    {
        enum class DrawType { Color, Texture };

        Sprite();
        Sprite(const std::string& path, float scale);
        Sprite(const Ref<GLTexture>& texture, float scale);
        Sprite(const glm::vec4& color);

        void LoadTexture(const std::string& path);
        void LoadTexture(const Ref<GLTexture>& texture);
        
        void SetSubTexture(float x, float y, float spriteWidth, float spriteHeight);
        void SetSubTexture(const Ref<SubTexture>& subTexture);
        
        void ResetScale();
        void ResetSubTexture();

        float Scale;

        Ref<SubTexture> Subtexture;
        Ref<GLTexture> Texture;
        DrawType Drawtype;

        glm::vec4 Color { 1.f };
        glm::vec2 ScaleVec2 { 0.f };

        bool UseColorAsTint;
        bool UseFixedScale = true;

    };
}

