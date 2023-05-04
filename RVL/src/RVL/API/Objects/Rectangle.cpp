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

    Ref<Rectangle> Rectangle::Create(const Transform& transform, const glm::vec3& color)
    {
        return std::make_shared<Rectangle>(transform, color);
    }

    Ref<Rectangle> Rectangle::Create(const glm::vec3& position, const glm::vec2& size, const glm::vec3& color)
    {
        return std::make_shared<Rectangle>(position, size, color);
    }

    Rectangle::Rectangle() : Entity()
    {
        _color = {1.f, 1.f, 1.f};
    }

    Rectangle::Rectangle(const Transform& transform, const glm::vec3& color) : Entity(transform)
    {
        _color = color;
    }

    Rectangle::Rectangle(const glm::vec3& position, const glm::vec2& size, const glm::vec3& color) : Entity(Transform(position, 0.f, size))
    {
        _color = color;
    }

    Rectangle::~Rectangle() {}

    void Rectangle::Draw()
    {
        Renderer::DrawRect(_transform, _color);
    }

    glm::vec3 Rectangle::GetColor() const
    {
        return _color;
    }

    void Rectangle::SetColor(const glm::vec3& color)
    {
        _color = color;
    }

}
