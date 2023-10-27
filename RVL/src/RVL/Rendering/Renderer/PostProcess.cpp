#include "PostProcess.hpp"

#include <Rendering/OpenGL/GLFrameBuffer.hpp>
#include <Rendering/OpenGL/GLVertexArray.hpp>
#include <Rendering/OpenGL/GLBuffer.hpp>
#include <Rendering/OpenGL/GLTexture.hpp>
#include <Rendering/OpenGL/GLShaderProgram.hpp>

#include "Renderer3D.hpp"

namespace Rvl
{
    PostProcess::PostProcess(const Ref<GLFrameBuffer>& fbo, const std::string& shader) : _fbo(fbo)
    {
        _screenVao = NewRef<GLVertexArray>();

        std::vector<ScreenVertex>(screenVertices) = 
        {
            {{-1.f, -1.f}, {0.0f, 0.0f}},
            {{1.f, -1.f}, {1.0f, 0.0f}},
            {{1.f, 1.f}, {1.f, 1.f}},
            {{-1.f, 1.f}, {0.f, 1.f}}
        };

        _screenVbo = NewRef<GLVertexBuffer>(screenVertices);
        _screenVbo->SetLayout({
            { ElementType::Vec2, 0, sizeof(ScreenVertex), false },
            { ElementType::Vec2, offsetof(ScreenVertex, TexCoord), sizeof(ScreenVertex), false }
        });

        std::vector<uint32> screenIndicies = { 0, 1, 2, 2, 3, 0 };
        Ref<GLIndexBuffer> ibo = NewRef<GLIndexBuffer>(screenIndicies);    

        _screenVao->SetSingleVertexBuffer(_screenVbo);
        _screenVao->AddIndexBuffer(ibo);

        _screenShader = NewRef<GLShaderProgram>(shader + ".vert", shader + ".frag");
        _screenShader->Bind();
    }

    PostProcess::~PostProcess() {}

    void PostProcess::Begin()
    {
        _fbo->Resize(RenderCommand::GetViewport());
        _fbo->Bind();
        RenderCommand::Clear();
    }

    void PostProcess::End()
    {
        _fbo->Unbind();
        GLTexture::BindTextureUnit(_fbo->GetColorAttachment(), 0);
        _screenShader->Bind();
        _screenShader->SetUniformInt("u_ScreenTexture", 0);
        Renderer3D::SubmitVa(_screenVao, _screenShader);
        _screenShader->Unbind();

    }
}
