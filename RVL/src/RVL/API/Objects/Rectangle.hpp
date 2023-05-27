#ifndef RVL_RECTANGLE_HPP
#define RVL_RECTANGLE_HPP

#include <Core/Core.hpp>
#include "Entity.hpp"
#include "Renderable.hpp"

namespace rvl
{
    class GLVertexBuffer;
    class GLIndexBuffer;
    class GLVertexArray;
    class GLShaderProgram;

    class Rectangle : public Entity, public Renderable
    {
    public:
        static Ref<Rectangle> Create();
        static Ref<Rectangle> Create(const Transform& transform, const glm::vec3& color);
        static Ref<Rectangle> Create(const glm::vec3& position, const glm::vec2& size, const glm::vec3& color = {1.f, 1.f, 1.f});

        Rectangle();
        Rectangle(const Transform& transform, const glm::vec3& color);
        Rectangle(const glm::vec3& position, const glm::vec2& size, const glm::vec3& color = {1.f, 1.f, 1.f});
        ~Rectangle();

        void Draw() override;

        glm::vec3 GetColor() const;
        float* GetColorPtr();
        
        void SetColor(const glm::vec3& color);

    private:
        glm::vec3 _color;
    };
}

#endif
