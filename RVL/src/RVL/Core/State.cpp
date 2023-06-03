#include "State.hpp"

#include <Core.hpp>
#include "Rendering/Renderer/Renderer.hpp"
#include "Rendering/Renderer/PerspectiveCamera.hpp"
#include "Rendering/Renderer/OrthographicCamera.hpp"
#include "Rendering/OpenGL/GLFrameBuffer.hpp"

namespace Rvl
{ 
    State::State() {}
    State::~State() {}

    void State::Tick() {}

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
            Renderer::Clear();
        }

        int viewport[2];
        Renderer::GetViewport(viewport);

        Renderer::BeginContext(*_camera->GetCamera(), viewport[0], viewport[1]);
    }

    void State::End()
    {
        Renderer::EndContext();
        
        if (_fbo)
            _fbo->Unbind();
    }
}
