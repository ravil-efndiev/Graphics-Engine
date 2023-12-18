#pragma once

#include <Core/Core.hpp>
#include "API/ECS/General/Transform.hpp"
#include "SubTexture.hpp"
#include "RenderCommand.hpp"

namespace Rvl
{
    class GLVertexArray;
    class GLVertexBuffer;
    class GLShaderProgram;
    class GLTexture;
    class Camera;

    class Renderer
    {
    public:
        static void Init();
        static void Shutdown();

        static void DrawRect(const Transform& transform, const glm::vec4& color);
        static void DrawRect(const Transform& transform, const Ref<GLTexture>& texture, const glm::vec4& tintColor = {1.f, 1.f, 1.f, 1.f});
        static void DrawRect(const Transform& transform, const Ref<SubTexture>& subtexture, const glm::vec4& tintColor = {1.f, 1.f, 1.f, 1.f});

        static void BeginContext(const Ref<Camera>& camera, float viewportWidth, float viewportHeight);
        static void EndContext();

        static glm::vec2 ConvertToWorldCoords(double x, double y);
        static glm::vec2 ConvertToWorldCoords(double x, double y, const glm::vec2& pos);

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
        static void BeginBatch();
        static void FlushAndReset();

    private:
        static glm::mat4 _projview;

        static constexpr size_t _rectsPerCall = 10000;
        static constexpr size_t _verticiesPerCall = _rectsPerCall * 4;
        static constexpr size_t _indiciesPerCall = _rectsPerCall * 6;

        static Ref<GLVertexArray> _rectVao;
        static Ref<GLVertexBuffer> _rectVbo;

        static Ref<GLShaderProgram> _textureShader;
        static Ref<GLShaderProgram> _lineShader;

        static uint32_t _rectIndiciesCount;

        static std::array<Ref<GLTexture>, 16> _textureSlots;
        static int _textureSlotIndex;

        static const glm::vec4 _rectVertexPositions[4];
    };
}

