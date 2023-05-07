#ifndef RVL_RENDERER_HPP
#define RVL_RENDERER_HPP

#include <Core/Core.hpp>
#include "Transform.hpp"

namespace rvl
{
    class GLVertexArray;
    class GLVertexBuffer;
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

        static void CreateContext(OrthographicCamera& camera, float viewportWidth, float viewportHeight);
        static void ShutdownContext();

        static void GetViewport(int rViewport[2]);
        static glm::vec2 ConvertToWorldCoords(double x, double y);

    private:
        static inline void DrawIndicies(GLVertexArray& vertexArray, int indexCount = 0);

        static constexpr uint32_t _rectsPerCall = 5000;
        static constexpr uint32_t _verticiesPerCall = _rectsPerCall * 4;
        static constexpr uint32_t _indiciesPerCall = _rectsPerCall * 6;

        static uint32_t _rectIndexCount;

        static glm::mat4 _projview;

        static Ref<GLShaderProgram> _flatColorShader;
        static Ref<GLShaderProgram> _textureShader;
        static Ref<GLVertexArray> _rectVao;
        static Ref<GLVertexBuffer> _rectVbo;

        static glm::vec3 _clearColor;
    };
}

#endif
