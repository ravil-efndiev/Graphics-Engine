#include "SceneRenderer.hpp"
#include <Core/App.hpp>
#include <API/ECS/Entity.hpp>
#include <API/ECS/2D/Sprite.hpp>
#include <API/ECS/3D/Model.hpp>
#include <Rendering/OpenGL/GLTexture.hpp>
#include <Rendering/Renderer/Renderer.hpp>
#include <Rendering/Renderer/Renderer3D.hpp>
#include <Rendering/Renderer/RenderCommand.hpp>

namespace Rvl
{

    void SceneRenderer::Render(const Ref<Scene>& scene, const Ref<UserCamera>& camera)
    {
        for (Entity entity : scene->GetEntities())
        {
            if (entity.Has<Model>())
            {
                scene->DrawModel(entity);   
            }
            
            if (entity.Has<Sprite>())
            {
                scene->DrawSprite(entity);   
            }
        }

    }
}
