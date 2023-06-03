#ifndef RVL_SPRITE_HPP
#define RVL_SPRITE_HPP

#include <Core/Core.hpp>
#include "Renderable.hpp"
#include "Entity.hpp"

namespace Rvl
{
    class GLTexture;
    class SubTexture;

    class Sprite : public Entity, public Renderable
    {
    public:
        static Ref<Sprite> Create();
        static Ref<Sprite> Create(const glm::vec3& position, float scale);

        Sprite();
        Sprite(const glm::vec3& position, float scale);
        ~Sprite();

        void LoadTexture(const std::string& path);
        void LoadTexture(const Ref<GLTexture>& texture);
        void SetSubTexture(float x, float y, float spriteWidth, float spriteHeight);
        void SetSubTexture(const Ref<SubTexture>& subTexture);
        void ResetScale();
        void ResetSubTexture();

        void Draw() override;
        void Draw(const glm::vec4& tintColor) override;

        Ref<GLTexture> GetTexture() const;

    private:
        float _scale;

        Ref<SubTexture> _subTexture;
        Ref<GLTexture> _texture;
    };

}

#endif
