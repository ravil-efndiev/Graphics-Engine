#include "Renderer.hpp"
#include "Rendering/OpenGL/GLVertexArray.hpp"
#include "Rendering/OpenGL/GLShaderProgram.hpp"
#include "OrthographicCamera.hpp"
#include "PerspectiveCamera.hpp"

namespace rvl
{
    glm::mat4 Renderer::_projview (1.0f);

    void Renderer::Init()
    {
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    }

    void Renderer::SubmitGeometry(GLVertexArray &vertexArray, GLShaderProgram &shader)
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
        vertexArray.UnbindIndexBuffer();
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

    void Renderer::GetViewport(int rViewport[2])
    {
        int viewport[4];
        glGetIntegerv(GL_VIEWPORT, viewport);

        rViewport[0] = viewport[2];
        rViewport[1] = viewport[3];
    }

    glm::vec2 Renderer::ConvertToWorldCoords(double x, double y)
    {
        int viewport[2];
        GetViewport(viewport);
        glm::vec4 vec4viewport (0, 0, viewport[0], viewport[1]);
        glm::vec3 pos (x, viewport[1] - y, 0);

        glm::vec3 worldCoords = glm::unProject(pos, glm::mat4(1.0f), _projview, vec4viewport);
        return glm::vec2(worldCoords.x, worldCoords.y);
    }
}
