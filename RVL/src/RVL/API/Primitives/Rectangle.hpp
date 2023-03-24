#ifndef RVL_RECTANGLE_HPP
#define RVL_RECTANGLE_HPP

#include <API/Primitives/Entity.hpp>
#include <Rvlpch.hpp>

namespace rvl
{
    class GLVertexBuffer;
    class GLIndexBuffer;
    class GLVertexArray;
    class GLShaderProgram;

    class Rectangle : public Entity
    {
    friend class RvlScene;

    public:
        Rectangle(const Vector2f& position, const Vector2f& size);
        Rectangle(const Vector2f& position, const Vector2f& size, const Vector3f& color);
        Rectangle(float x, float y, float width, float height);
        Rectangle(float x, float y, float width, float height, const Vector3f& color);

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
    };
}

#endif
