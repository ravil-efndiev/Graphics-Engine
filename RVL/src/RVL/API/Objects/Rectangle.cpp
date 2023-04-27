#include "Rectangle.hpp"

#include "Rendering/OpenGL/GLShaderProgram.hpp"
#include "Rendering/OpenGL/GLVertexArray.hpp"
#include "Rendering/OpenGL/GLBuffer.hpp"

#include "Rendering/Renderer/Renderer.hpp"

#include <Rvlglpch.hpp>

namespace rvl
{
    Ref<Rectangle> Rectangle::Create()
    {
        return std::make_shared<Rectangle>();
    }

    Ref<Rectangle> Rectangle::Create(const Vector2f &position, const Vector2f &size, const Vector3f &color)
    {
        return std::make_shared<Rectangle>(position, size, color);
    }

    Ref<Rectangle> Rectangle::Create(float x, float y, float width, float height, const Vector3f &color)
    {
        return std::make_shared<Rectangle>(x, y, width, height, color);
    }

    Rectangle::Rectangle() : Entity(0.f, 0.f)
    {
        _color = {1.f, 1.f, 1.f};
        _width = 1.f;
        _height = 1.f;

        InitProps();
    }

    Rectangle::Rectangle(const Vector2f &position, const Vector2f &size, const Vector3f &color) : _color(color)
    {
        _width = size.X();
        _height = size.Y();

        InitProps();
        GenerateMesh();
    }

    Rectangle::Rectangle(float x, float y, float width, float height, const Vector3f &color) : _width(width), _height(height), _color(color) 
    {
        _position = Vector2f(x, y);

        InitProps();
        GenerateMesh();
    }
    
    Rectangle::~Rectangle() {}

    void Rectangle::Draw()
    {
        Renderer::SubmitGeometry(*_vao, *_shaderProgram);
    }

    void Rectangle::SetColor(const Vector3f& color)
    {
        _color = color;
        ResetColor();
    }

    Vector3f Rectangle::Color()
    {
        return _color;
    }

    void Rectangle::InitProps()
    {
        Width = Property<float>(
            &_width,
            [this]() -> float { return _width; },
            [this](float value) 
            { 
                _width = value; 
                ResetPosition();
            }
        );

        Height = Property<float>(
            &_height,
            [this]() -> float { return _height; },
            [this](float value) 
            { 
                _height = value; 
                ResetPosition();
            }
        );
    }

    void Rectangle::GenerateMesh()
    {
        _vao = std::make_shared<GLVertexArray>();
        _positionVbo = std::make_shared<GLVertexBuffer>(std::vector<glm::vec3>
            {
                {-(_width/2)  + _position.X(), -(_height/2) + _position.Y(), 0.0f},
                {_width/2 + _position.X(), -(_height/2) + _position.Y(), 0.0f},
                {_width/2 + _position.X(), _height/2 + _position.Y(), 0.0f},
                {-(_width/2)  + _position.X(), _height/2 + _position.Y(), 0.0f},
            }
        );

        RVL_LOG(_color.X());

        _colorVbo = std::make_shared<GLVertexBuffer>(std::vector<glm::vec3>
            {
                {_color.X(), _color.Y(), _color.Z()},
                {_color.X(), _color.Y(), _color.Z()},
                {_color.X(), _color.Y(), _color.Z()},
                {_color.X(), _color.Y(), _color.Z()},
            }
        );

        _indicies = std::make_shared<GLIndexBuffer>(std::vector<uint32_t>({0, 1, 2, 2, 3, 0}));

        _vao->AddVertexBuffer(_positionVbo);
        _vao->AddVertexBuffer(_colorVbo);
        _vao->AddIndexBuffer(_indicies);

        _shaderProgram = std::make_unique<GLShaderProgram>("../RVL/res/shaders/main.vert", "../RVL/res/shaders/main.frag");
        _shaderProgram->BindAttribute(RVL_POSITION_LOCATION, "position");
        _shaderProgram->BindAttribute(RVL_COLOR_LOCATION, "color");
        _shaderProgram->Link();
    }

    void Rectangle::ResetPosition()
    {
        GLVertexBuffer newPos
        (
            {
                {-(_width/2)  + _position.X(), -(_height/2) + _position.Y(), 0.0f},
                {_width/2 + _position.X(), -(_height/2) + _position.Y(), 0.0f},
                {_width/2 + _position.X(), _height/2 + _position.Y(), 0.0f},
                {-(_width/2)  + _position.X(), _height/2 + _position.Y(), 0.0f},
            }
        );

        _vao->ResetVertexBuffer(RVL_POSITION_LOCATION, newPos);
    }

    void Rectangle::ResetColor()
    {
        GLVertexBuffer newColor
        (
            std::vector<glm::vec3>
            {
                {_color.X(), _color.Y(), _color.Z()},
                {_color.X(), _color.Y(), _color.Z()},
                {_color.X(), _color.Y(), _color.Z()},
                {_color.X(), _color.Y(), _color.Z()},
            }
        );

        _vao->ResetVertexBuffer(RVL_COLOR_LOCATION, newColor);
    }
}
