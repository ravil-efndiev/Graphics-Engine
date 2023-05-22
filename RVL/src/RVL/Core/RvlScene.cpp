#include "RvlScene.hpp"

#include <Core.hpp>
#include "Rendering/Renderer/Renderer.hpp"
#include "Rendering/Renderer/PerspectiveCamera.hpp"
#include "Rendering/Renderer/OrthographicCamera.hpp"
#include "Rendering/OpenGL/GLFrameBuffer.hpp"

namespace rvl
{ 
    RvlScene::RvlScene()
    {
    }

    RvlScene::~RvlScene() {}

    void RvlScene::Tick() {}

    void RvlScene::AddFrameBuffer(const Ref<GLFrameBuffer>& fbo)
    {
        _fbo = fbo;
    }

    void RvlScene::Begin()
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

    void RvlScene::End()
    {
        Renderer::EndContext();
        
        if (_fbo)
            _fbo->Unbind();
    }
}
