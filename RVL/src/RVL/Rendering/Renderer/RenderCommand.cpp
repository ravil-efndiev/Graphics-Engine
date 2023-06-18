#include "RenderCommand.hpp"

#include "Rendering/OpenGL/GLVertexArray.hpp"
#include "Rendering/OpenGL/GLShaderProgram.hpp"
#include "Rendering/OpenGL/GLTexture.hpp"

namespace Rvl
{
    glm::vec3 RenderCommand::_clearColor;

    void RenderCommand::GetViewport(int rViewport[2])
    {
        int viewport[4];
        glGetIntegerv(GL_VIEWPORT, viewport);

        rViewport[0] = viewport[2];
        rViewport[1] = viewport[3];
    }

    void RenderCommand::SetViewport(const glm::vec2& viewport)
    {
        glViewport(0, 0, viewport.x, viewport.y);
    }

    void RenderCommand::SetClearColor(const glm::vec3& clearColor)
    {
        _clearColor = clearColor;
    }

    void RenderCommand::Clear()
    {
        glClearColor(_clearColor.r, _clearColor.g, _clearColor.b, 1.f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    void RenderCommand::DrawIndicies(const Ref<GLVertexArray>& vertexArray, int indexCount)
    {
        int count = indexCount ? indexCount : vertexArray->GetIndexBuffer()->GetIndiciesCount();
        vertexArray->Bind();
        vertexArray->BindIndexBuffer();
        glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, nullptr);
        vertexArray->UnbindIndexBuffer();
        vertexArray->Unbind();
    }

    void RenderCommand::DrawIndicies(GLVertexArray& vertexArray, int indexCount)
    {
        int count = indexCount ? indexCount : vertexArray.GetIndexBuffer()->GetIndiciesCount();
        vertexArray.Bind();
        vertexArray.BindIndexBuffer();
        glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, nullptr);
        vertexArray.UnbindIndexBuffer();
        vertexArray.Unbind();
    }
}
