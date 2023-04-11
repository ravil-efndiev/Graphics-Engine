#include "RvlScene.hpp"
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


    void RvlScene::SetCamera(const std::shared_ptr<OrthographicCamera>& cam)
    {
        _camera2d = cam;
    }

    void RvlScene::MakeScene()
    {
        int viewport[2];
        Renderer::GetVeiwport(viewport);

        Renderer::CreateScene2D(*_camera2d, viewport[0], viewport[1]);
        //Renderer::CreateScene3D(*_camera, viewport[0], viewport[1]);
    }
}
