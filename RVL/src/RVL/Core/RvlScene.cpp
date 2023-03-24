#include "RvlScene.hpp"
#include "Rendering/Renderer/Renderer.hpp"

namespace rvl
{
    RvlScene::RvlScene()
    {
        _entities = {};
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


    void RvlScene::SetCamera(const std::shared_ptr<PerspectiveCamera>& cam)
    {
        _camera = cam;
    }

    void RvlScene::AddEntity(const std::shared_ptr<Entity>& entity)
    {
        _entities.push_back(entity);
    }

    void RvlScene::MakeScene()
    {
        int viewport[2];
        Renderer::GetVeiwport(viewport);

        Renderer::CreateScene(*_camera, viewport[0], viewport[1]);
    }
}
