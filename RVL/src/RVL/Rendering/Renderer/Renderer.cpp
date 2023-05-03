#include "Renderer.hpp"
#include "Rendering/OpenGL/GLVertexArray.hpp"
#include "Rendering/OpenGL/GLShaderProgram.hpp"
#include "Rendering/OpenGL/GLTexture.hpp"
#include "OrthographicCamera.hpp"
#include "PerspectiveCamera.hpp"

namespace rvl
{
    glm::mat4 Renderer::_projview (1.0f);

    Ref<GLShaderProgram> Renderer::_flatColorShader;
    Ref<GLShaderProgram> Renderer::_textureShader;
    Ref<GLVertexArray> Renderer::_rectVao;

    glm::vec3 Renderer::_clearColor;

    void Renderer::Init()
    {
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        _rectVao = CreateRef<GLVertexArray>();

        Ref<GLVertexBuffer> rectVbo = CreateRef<GLVertexBuffer>(std::vector<glm::vec3>
            {
                {-0.5f, -0.5f, 0.0f},
                {0.5f, -0.5f, 0.0f},
                {0.5f, 0.5f, 0.0f},
                {-0.5f, 0.5f, 0.0f},
            }
        );

        Ref<GLVertexBuffer> rectTextureCoords = CreateRef<GLVertexBuffer>(std::vector<glm::vec2>
            {
                {0.0f, 0.0f},
                {1.0f, 0.0f},
                {1.0f, 1.0f},
                {0.0f, 1.0f}
            }
        );

        Ref<GLIndexBuffer> rectIndicies = CreateRef<GLIndexBuffer>(
            std::vector<uint32_t> {0, 1, 2, 2, 3, 0}
        );

        _rectVao->AddVertexBuffer(rectVbo);
        _rectVao->AddVertexBuffer(rectTextureCoords);
        _rectVao->AddIndexBuffer(rectIndicies);

        _flatColorShader = CreateRef<GLShaderProgram>("../RVL/res/shaders/main.vert", "../RVL/res/shaders/main.frag");
        _flatColorShader->BindAttribute(RVL_POSITION_LOCATION, "position");
        _flatColorShader->Link();

        _textureShader = CreateRef<GLShaderProgram>("../RVL/res/shaders/textured.vert", "../RVL/res/shaders/textured.frag");
        _textureShader->BindAttribute(0, "position");
        _textureShader->BindAttribute(1, "coords");
        _textureShader->Link();
    }

    void Renderer::CreateScene(OrthographicCamera& camera, float viewportWidth, float viewportHeight)
    {
        _projview = camera.GetProjectionMatrix(viewportWidth, viewportHeight) * camera.GetViewMatrix();

        _flatColorShader->Bind();
        _flatColorShader->SetUniform("u_Projview", _projview);

        _textureShader->Bind();
        _textureShader->SetUniform("u_Projview", _projview);
    }

    void Renderer::ShutdownScene()
    {
        _flatColorShader->Unbind();
        _textureShader->Unbind();
        _projview = glm::mat4(1.f);
    }

    void Renderer::SubmitGeometry(GLVertexArray& vertexArray, GLShaderProgram& shader)
    {
        shader.Bind();
        shader.SetUniform("projview", _projview);
        DrawIndicies(vertexArray);
        shader.Unbind();
    }

    void Renderer::DrawRect(const Transform& transform, const glm::vec3& color)
    {
        _flatColorShader->Bind();
        _flatColorShader->SetUniform("u_Color", glm::vec4(color, 1.f));

        auto rTransform = const_cast<Transform&>(transform);

        _flatColorShader->SetUniform("u_Transform", rTransform.GetMatrix());

        DrawIndicies(*_rectVao);
        _flatColorShader->Unbind();
    }

    void Renderer::DrawRect(const Transform& transform, const GLTexture& texture)
    {
        _textureShader->Bind();

        auto rTransform = const_cast<Transform&>(transform);

        _textureShader->SetUniform("u_Transform", rTransform.GetMatrix());

        _textureShader->SetUniform("u_Texture", texture.GetUnit());

        texture.Bind();
        DrawIndicies(*_rectVao);
        texture.Unbind();

        _textureShader->Unbind();
    }

    inline void Renderer::DrawIndicies(GLVertexArray& vertexArray)
    {
        vertexArray.Bind();
        vertexArray.BindIndexBuffer();
        glDrawElements(GL_TRIANGLES, vertexArray.GetIndexBuffer()->GetIndiciesCount(), GL_UNSIGNED_INT, nullptr);
        vertexArray.UnbindIndexBuffer();
        vertexArray.Unbind();
    }

    void Renderer::SetClearColor(const glm::vec3& clearColor)
    {
        _clearColor = clearColor;
    }

    void Renderer::Clear()
    {
        glClearColor(_clearColor.r, _clearColor.g, _clearColor.b, 1.f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
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
