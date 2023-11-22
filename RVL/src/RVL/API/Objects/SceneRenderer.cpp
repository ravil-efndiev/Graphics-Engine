#include "SceneRenderer.hpp"
#include <API/ECS/Entity.hpp>
#include <API/ECS/2D/SpriteComponent.hpp>
#include <API/ECS/3D/ModelComponent.hpp>

namespace Rvl
{
    void SceneRenderer::Render(Scene& scene, PriorityComponent priority)
    {
        for (Entity entity : scene.GetEntities())
        {
            if (entity.Has<SpriteComponent>() && entity.Has<ModelComponent>())
            {
                if (priority == PriorityComponent::Sprite)
                    scene.DrawSprite(entity);
                else if (priority == PriorityComponent::Model)
                    scene.DrawModel(entity);
            }

            else if (entity.Has<SpriteComponent>())
            {
                scene.DrawSprite(entity);   
            }   

            else if (entity.Has<ModelComponent>())
            {
                scene.DrawModel(entity);   
            }   
        }
    }
}
