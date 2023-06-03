#ifndef RVL_RENDERER_HPP
#define RVL_RENDERER_HPP

#include <Core/Core.hpp>
#include "Transform.hpp"
#include "SubTexture.hpp"

namespace Rvl
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
        static void Shutdown();

        static void SubmitGeometry(GLVertexArray& vertexArray, GLShaderProgram& shader);
        static void DrawRect(const Transform& transform, const glm::vec4& color);
        static void DrawRect(const Transform& transform, const Ref<GLTexture>& texture, const glm::vec4& tintColor = {1.f, 1.f, 1.f, 1.f});
        static void DrawRect(const Transform& transform, const Ref<SubTexture>& subtexture, const glm::vec4& tintColor = {1.f, 1.f, 1.f, 1.f});

        static void SetClearColor(const glm::vec3& clearColor);
        static void Clear();

        static void BeginContext(OrthographicCamera& camera, float viewportWidth, float viewportHeight);
        static void EndContext();

        static void GetViewport(int rViewport[2]);
        static void SetViewport(const glm::vec2& viewport);

        static glm::vec2 ConvertToWorldCoords(double x, double y);

        struct Statistics
        {
            int DrawCalls;
            int RectCount;
            int VerticiesCount;
            int IndiciesCount;
        };

        static Statistics GetStats();
        static void ResetStats();

    private:
        static void DrawIndicies(const Ref<GLVertexArray>& vertexArray, int indexCount = 0);
        static void DrawIndicies(GLVertexArray& vertexArray, int indexCount = 0);

        static void BeginBatch();
        static void FlushAndReset();

    private:
        static glm::mat4 _projview;
        static glm::vec3 _clearColor;

        static constexpr size_t _rectsPerCall = 10000;
        static constexpr size_t _verticiesPerCall = _rectsPerCall * 4;
        static constexpr size_t _indiciesPerCall = _rectsPerCall * 6;

        static Ref<GLVertexArray> _rectVao;
        static Ref<GLVertexBuffer> _rectPositionVbo;
        static Ref<GLVertexBuffer> _rectColorVbo;
        static Ref<GLVertexBuffer> _rectTexctureCoordsVbo;
        static Ref<GLVertexBuffer> _rectTextureIndexVbo;
        static Ref<GLShaderProgram> _textureShader;

        static uint32_t _rectIndiciesCount;

        static std::vector<glm::vec3> _rectPositionVBOData;
        static std::vector<glm::vec4> _rectColorVBOData;
        static std::vector<glm::vec2> _rectTexCoordsVBOData;
        static std::vector<float> _rectTexIndexVBOData;

        static std::array<Ref<GLTexture>, 16> _textureSlots;
        static int _textureSlotIndex;

        static const glm::vec4 _rectVertexPositions[4];
    };
}

#endif
