#ifndef RVL_RENDERER_HPP
#define RVL_RENDERER_HPP

#include <Core/Core.hpp>
#include "Transform.hpp"

namespace rvl
{
    class GLVertexArray;
    class GLShaderProgram;
    class GLTexture;
    class PerspectiveCamera;
    class OrthographicCamera;

    class Renderer
    {
    public:
        static void Init();

        static void SubmitGeometry(GLVertexArray& vertexArray, GLShaderProgram& shader);
        static void DrawRect(const Transform& transform, const glm::vec3& color);
        static void DrawRect(const Transform& transform, const GLTexture& texture);

        static void SetClearColor(const glm::vec3& clearColor);
        static void Clear();

        static void CreateScene(OrthographicCamera& camera, float viewportWidth, float viewportHeight);
        static void ShutdownScene();

        static void GetViewport(int rViewport[2]);
        static glm::vec2 ConvertToWorldCoords(double x, double y);

    private:
        static inline void DrawIndicies(GLVertexArray& vertexArray);

        static glm::mat4 _projview;

        static Ref<GLShaderProgram> _flatColorShader;
        static Ref<GLShaderProgram> _textureShader;
        static Ref<GLVertexArray> _rectVao;

        static glm::vec3 _clearColor;
    };
}

#endif
