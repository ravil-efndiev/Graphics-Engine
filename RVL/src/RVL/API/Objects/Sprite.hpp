#ifndef RVL_SPRITE_HPP
#define RVL_SPRITE_HPP

#include <Core/Core.hpp>
#include "Entity.hpp"

namespace rvl
{
    class GLVertexBuffer;
    class GLIndexBuffer;
    class GLVertexArray;
    class GLShaderProgram;
    class GLTexture;

    class Sprite : public Entity
    {
    public:
        template <class ... Args>
        static Ref<Sprite> Create(Args&& ...args);

        Sprite();
        Sprite(const Vector2f& position);
        Sprite(float x, float y);
        ~Sprite();

        void LoadTexture(const std::string& filename);

        void Draw() override;

    private:
        static int _unit;

        std::unique_ptr<GLTexture> _texture;
        
        std::unique_ptr<GLVertexArray> _vao;
        std::shared_ptr<GLVertexBuffer> _positionVbo;
        std::shared_ptr<GLVertexBuffer> _colorVbo;
        std::shared_ptr<GLVertexBuffer> _textureCoordsVbo;
        std::shared_ptr<GLIndexBuffer> _indicies;

        std::unique_ptr<GLShaderProgram> _shaderProgram;

        void GenerateMesh();

        void ResetPosition() override;
    };

    template <class... Args>
    inline Ref<Sprite> Sprite::Create(Args &&...args)
    {
        return std::make_shared<Sprite>(args...);
    }
}

#endif
