#pragma once

#include <Core/Core.hpp>
#include <glm/glm.hpp>

namespace Rvl
{
    class GLFrameBuffer;
    class GLVertexBuffer;
    class GLVertexArray;
    class GLShaderProgram;

    struct ScreenVertex
    {
        glm::vec2 Position;
        glm::vec2 TexCoord;
    };

    class PostProcess
    {
    public:
        PostProcess(const Ref<GLFrameBuffer>& fbo, const std::string& shader);
        ~PostProcess();

        void Begin();
        void End();

    private:
        Ref<GLFrameBuffer> _fbo;

        Ref<GLVertexArray> _screenVao;
        Ref<GLVertexBuffer> _screenVbo;
        Ref<GLShaderProgram> _screenShader;

    };
}

