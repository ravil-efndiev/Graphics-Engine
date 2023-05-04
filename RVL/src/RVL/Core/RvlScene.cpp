#include "RvlScene.hpp"

#include <Core.hpp>
#include "Rendering/Renderer/Renderer.hpp"
#include "Rendering/Renderer/PerspectiveCamera.hpp"
#include "Rendering/Renderer/OrthographicCamera.hpp"

namespace rvl
{ 
    RvlScene::RvlScene()
    {
    }

    RvlScene::~RvlScene() {}

    void RvlScene::Start()
    {
    }

    void RvlScene::Update()
    {
    }

    void RvlScene::Render()
    {
    }

    void RvlScene::Begin()
    {
        if (!_camera) throw Error("camera was not initialized during scene creation", RVL_RUNTIME_ERROR);

        int viewport[2];
        Renderer::GetViewport(viewport);

        Renderer::CreateContext(*_camera->GetCamera(), viewport[0], viewport[1]);
    }

    void RvlScene::End()
    {
        Renderer::ShutdownContext();
    }
}
