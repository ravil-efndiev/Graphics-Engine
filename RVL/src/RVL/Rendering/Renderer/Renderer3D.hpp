#pragma once
#include <Core/Core.hpp>
#include "Camera.hpp"
#include "RenderCommand.hpp"

namespace Rvl
{
    class GLVertexArray;
    class GLVertexBuffer;
    class GLShaderProgram;
    class GLTexture;

    class Renderer3D
    {
    public:
        static void BeginContext(const Ref<Camera>& camera, float viewportWidth, float viewportHeight);
        static void EndContext();

        static void Submit(GLVertexArray& vertexArray, GLShaderProgram& shader);
        static void Submit(const Ref<GLVertexArray>& vertexArray, const Ref<GLShaderProgram>& shader);

    private:
        static glm::mat4 _projview;

    };
}

