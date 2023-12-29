#include "RenderApi.hpp"

#include "Rendering/OpenGL/GLVertexArray.hpp"
#include "Rendering/OpenGL/GLShaderProgram.hpp"
#include "Rendering/OpenGL/GLTexture.hpp"

namespace Rvl
{
    glm::vec3 RenderApi::_clearColor;

    glm::vec2 RenderApi::GetViewport()
    {
        int viewport[4];
        glGetIntegerv(GL_VIEWPORT, viewport);

        return { viewport[2], viewport[3] };
    }

    void RenderApi::SetViewport(const glm::vec2& viewport)
    {
        glViewport(0, 0, viewport.x, viewport.y);
    }

    void RenderApi::SetClearColor(const glm::vec3& clearColor)
    {
        _clearColor = clearColor;
    }

    void RenderApi::Clear()
    {
        glClearColor(_clearColor.r, _clearColor.g, _clearColor.b, 1.f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    void RenderApi::DrawIndicies(const Ref<GLVertexArray>& vertexArray, int indexCount)
    {
        int count = indexCount ? indexCount : vertexArray->GetIndexBuffer()->GetIndiciesCount();
        vertexArray->Bind();
        vertexArray->BindIndexBuffer();
        glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, nullptr);
        vertexArray->UnbindIndexBuffer();
        vertexArray->Unbind();
    }

    void RenderApi::DrawIndicies(GLVertexArray& vertexArray, int indexCount)
    {
        int count = indexCount ? indexCount : vertexArray.GetIndexBuffer()->GetIndiciesCount();
        vertexArray.Bind();
        vertexArray.BindIndexBuffer();
        glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, nullptr);
        vertexArray.UnbindIndexBuffer();
        vertexArray.Unbind();
    }

    void RenderApi::DrawIndiciesInstanced(const Ref<GLVertexArray>& vertexArray, int instances, int indexCount)
    {
        int count = indexCount ? indexCount : vertexArray->GetIndexBuffer()->GetIndiciesCount();
        vertexArray->Bind();
        vertexArray->BindIndexBuffer();
        glDrawElementsInstanced(GL_TRIANGLES, count, GL_UNSIGNED_INT, nullptr, instances);
        vertexArray->UnbindIndexBuffer();
        vertexArray->Unbind();
    }
    
    void RenderApi::DrawLines(const Ref<GLVertexArray>& vertexArray, int vertexCount)
    {
        vertexArray->Bind();
        glDrawArrays(GL_LINES, 0, vertexCount);
        vertexArray->Unbind();   
    }
    
    void RenderApi::DrawLines(GLVertexArray& vertexArray, int vertexCount)
    {
        vertexArray.Bind();
        glDrawArrays(GL_LINES, 0, vertexCount);
        vertexArray.Unbind();  
    }
}
