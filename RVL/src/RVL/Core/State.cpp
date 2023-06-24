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

    void State::AddFrameBuffer(const Ref<GLFrameBuffer>& fbo)
    {
        _fbo = fbo;
    }

    void State::Begin()
    {
        if (!_camera) throw Error("camera was not initialized during scene creation", RVL_RUNTIME_ERROR);

        if (_fbo)
        {
            _fbo->Bind();
            RenderCommand::Clear();
        }

        glm::vec2 viewport = RenderCommand::GetViewport();

        if (_mode == RenderMode::Mode_2D)
            Renderer::BeginContext(_camera->GetCamera(), viewport.x, viewport.y);
        else if (_mode == RenderMode::Mode_3D)
            Renderer3D::BeginContext(_camera->GetCamera(), viewport.x, viewport.y);
    }

    void State::End()
    {
        if (_mode == RenderMode::Mode_2D)
            Renderer::EndContext();
        else if (_mode == RenderMode::Mode_3D)
            Renderer3D::EndContext();
        
        if (_fbo)
            _fbo->Unbind();
    }
}
