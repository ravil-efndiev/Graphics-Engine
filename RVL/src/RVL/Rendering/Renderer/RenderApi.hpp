#pragma once

#include <Core/Core.hpp>
#include <glm/glm.hpp>

namespace Rvl
{
    class GLVertexArray;

    class RenderApi
    {
    public:
        static void SetClearColor(const glm::vec3& clearColor);
        static void Clear();        

        static glm::vec2 GetViewport();
        static void SetViewport(const glm::vec2& viewport);

        static void DrawIndicies(const Ref<GLVertexArray>& vertexArray, int indexCount = 0);
        static void DrawIndicies(GLVertexArray& vertexArray, int indexCount = 0);

        static void DrawLines(const Ref<GLVertexArray>& vertexArray, int vertexCount);
        static void DrawLines(GLVertexArray& vertexArray, int vertexCount);

    private:
        static glm::vec3 _clearColor;
    };
}

