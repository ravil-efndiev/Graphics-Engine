#ifndef RVL_SPRITE_HPP
#define RVL_SPRITE_HPP

#include <Core/Core.hpp>
#include <API/Property.hpp>
#include <Rendering/Renderer/Transform.hpp>

namespace rvl
{
    class GLTexture;

    class Sprite
    {
    public:
        static Ref<Sprite> Create();
        static Ref<Sprite> Create(const glm::vec3& position, float scale);

        Sprite();
        Sprite(const glm::vec3& position, float scale);
        ~Sprite();

        void LoadTexture(const std::string& path);
        void ResetScale();

        void Draw();

        Ref<GLTexture> GetTexture() const;

        Property<Transform> transform = {&_transform};

    private:
        Transform _transform;
        float _scale;

        Ref<GLTexture> _texture;
    };

}

#endif
