#ifndef RVL_RECTANGLE_HPP
#define RVL_RECTANGLE_HPP

#include <API/Objects/Entity.hpp>
#include <Core/Platform.hpp>

namespace rvl
{
    class GLVertexBuffer;
    class GLIndexBuffer;
    class GLVertexArray;
    class GLShaderProgram;

    class Rectangle : public Entity
    {
    public:
        template <class ... Args>
        static Ref<Rectangle> Create(Args&& ...args);

        Rectangle();
        Rectangle(const Vector2f& position, const Vector2f& size, const Vector3f& color = {1.f, 1.f, 1.f});
        Rectangle(float x, float y, float width, float height, const Vector3f& color = {1.f, 1.f, 1.f});

        ~Rectangle();

        void Draw() override;

        Vector3f GetColor() const;
        void SetColor(const Vector3f& color);

    private:
        float _width, _height;
        Vector3f _color;
        
        std::shared_ptr<GLVertexArray> _vao;
        std::shared_ptr<GLVertexBuffer> _positionVbo;
        std::shared_ptr<GLVertexBuffer> _colorVbo;
        std::shared_ptr<GLIndexBuffer> _indicies;

        std::unique_ptr<GLShaderProgram> _shaderProgram;

        void GenerateMesh();
        void ResetPosition() override;  
    };


    template <class... Args>
    inline Ref<Rectangle> Rectangle::Create(Args&& ...args)
    {
        return std::make_shared<Rectangle>(args...);
    }
}

#endif
