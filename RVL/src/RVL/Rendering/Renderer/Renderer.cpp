#include "Renderer.hpp"
#include "Rendering/OpenGL/GLVertexArray.hpp"
#include "Rendering/OpenGL/GLShaderProgram.hpp"
#include "OrthographicCamera.hpp"
#include "PerspectiveCamera.hpp"

namespace rvl
{
    glm::mat4 Renderer::_projview (1.0f);

    void Renderer::SubmitGeometry(GLVertexArray& vertexArray, GLShaderProgram& shader)
    {
        shader.Bind();
        shader.SetUniform("projview", _projview);
        DrawIndicies(vertexArray);
        shader.Unbind();
    }

    void Renderer::Clear(GLclampf red, GLclampf green, GLclampf blue, GLclampf alpha)
    {
        glClearColor(red, green, blue, alpha);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    inline void Renderer::DrawIndicies(GLVertexArray& vertexArray)
    {
        vertexArray.Bind();
        vertexArray.BindIndexBuffer();
        glDrawElements(GL_TRIANGLES, vertexArray.GetIndexBuffer()->GetIndiciesCount(), GL_UNSIGNED_INT, nullptr);
        vertexArray.Unbind();
    }

    void Renderer::CreateScene2D(OrthographicCamera& camera, float viewportWidth, float viewportHeight)
    {
        _projview = camera.GetProjectionMatrix(viewportWidth, viewportHeight) * camera.GetViewMatrix();
    }

    void Renderer::CreateScene3D(PerspectiveCamera& camera, float viewportWidth, float viewportHeight)
    {
        _projview = camera.GetProjectionMatrix(viewportWidth, viewportHeight) * camera.GetViewMatrix();
    }

    void Renderer::GetVeiwport(int rViewport[2])
    {
        int viewport[4];
        glGetIntegerv(GL_VIEWPORT, viewport);

        rViewport[0] = viewport[2];
        rViewport[1] = viewport[3];
    }
}
