#include "RvlState.hpp"

#include <Core.hpp>
#include "Rendering/Renderer/Renderer.hpp"
#include "Rendering/Renderer/PerspectiveCamera.hpp"
#include "Rendering/Renderer/OrthographicCamera.hpp"
#include "Rendering/OpenGL/GLFrameBuffer.hpp"

namespace rvl
{ 
    RvlState::RvlState() {}
    RvlState::~RvlState() {}

    void RvlState::Tick() {}

    void RvlState::AddFrameBuffer(const Ref<GLFrameBuffer>& fbo)
    {
        _fbo = fbo;
    }

    void RvlState::Begin()
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

    void RvlState::End()
    {
        Renderer::EndContext();
        
        if (_fbo)
            _fbo->Unbind();
    }
}
