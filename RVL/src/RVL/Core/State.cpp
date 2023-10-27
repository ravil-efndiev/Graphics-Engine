#include "State.hpp"

#include <Core.hpp>
#include "Rendering/Renderer/Renderer.hpp"
#include "Rendering/Renderer/Renderer3D.hpp"
#include "Rendering/Renderer/PerspectiveCamera.hpp"
#include "Rendering/Renderer/OrthographicCamera.hpp"
#include "Rendering/OpenGL/GLFrameBuffer.hpp"

namespace Rvl
{ 
    State::State(RenderMode mode) 
    {
        _mode = mode;
    }
    
    State::~State() {}

    void State::StartScene()
    {
        _currentScene.StartBehaviours();
    }

    void State::UpdateScene()
    {
        _currentScene.UpdateBehaviours();
    }

    void State::CreateFrameBuffer()
    {
        _fbo = NewRef<GLFrameBuffer>(RenderCommand::GetViewport());
    }

    void State::CreateFrameBuffer(const glm::vec2& size)
    {
        _fbo = NewRef<GLFrameBuffer>(size);
    }

    void State::Begin()
    {
        if (!_camera) throw Error("camera was not initialized during scene creation", RVL_RUNTIME_ERROR);

        glm::vec2 viewport = RenderCommand::GetViewport();

        if (_fbo) 
        {
            _fbo->Bind();
            RenderCommand::Clear();
        }
        
        if (_mode & RenderMode_3D)
            Renderer3D::BeginContext(_camera->GetCamera(), viewport.x, viewport.y);

        if (_mode & RenderMode_2D)
            Renderer::BeginContext(_camera->GetCamera(), viewport.x, viewport.y);
    }

    void State::End()
    {
        if (_mode & RenderMode_2D)
            Renderer::EndContext();

        if (_fbo) _fbo->Unbind();
    }
}
