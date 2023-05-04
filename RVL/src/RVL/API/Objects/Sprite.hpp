#ifndef RVL_SPRITE_HPP
#define RVL_SPRITE_HPP

#include <Core/Core.hpp>
#include "Entity.hpp"

namespace rvl
{
    class GLTexture;

    class Sprite : public Entity
    {
    public:
        static Ref<Sprite> Create();
        static Ref<Sprite> Create(const glm::vec3& position, float scale);

        Sprite();
        Sprite(const glm::vec3& position, float scale);
        ~Sprite();

        void LoadTexture(const std::string& path);
        void ResetScale();

        void Draw() override;

        Ref<GLTexture> GetTexture() const;

    private:
        float _scale;

        Ref<GLTexture> _texture;
    };

}

#endif
