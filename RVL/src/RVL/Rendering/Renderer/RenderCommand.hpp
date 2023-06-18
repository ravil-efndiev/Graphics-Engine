#pragma once

#include <Core/Core.hpp>
#include <glm/glm.hpp>

namespace Rvl
{
    class GLVertexArray;

    class RenderCommand
    {
    public:
        static void SetClearColor(const glm::vec3& clearColor);
        static void Clear();        

        static void GetViewport(int rViewport[2]);
        static void SetViewport(const glm::vec2& viewport);

        static void DrawIndicies(const Ref<GLVertexArray>& vertexArray, int indexCount = 0);
        static void DrawIndicies(GLVertexArray& vertexArray, int indexCount = 0);

    private:
        static glm::vec3 _clearColor;
    };
}

