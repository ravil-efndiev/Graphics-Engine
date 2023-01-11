#include "Renderer.hpp"
#include "Rendering/OpenGL/GLVertexArray.hpp"
#include "Rendering/OpenGL/GLShaderProgram.hpp"
#include "OrthographicCamera.hpp"

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
    }

    void Renderer::CreateScene(const OrthographicCamera& camera)
    {
        _projview = camera.GetProjectionMatrix() * camera.GetViewMatrix();
    }
    
}
