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

    void RvlScene::MakeScene()
    {
        if (!_camera) throw Error("camera was not initialized during scene creation", RVL_RUNTIME_ERROR);

        int viewport[2];
        Renderer::GetVeiwport(viewport);

        Renderer::CreateScene2D(*_camera->_camera, viewport[0], viewport[1]);
    }
}
