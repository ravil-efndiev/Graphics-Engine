#include "StandartSystems.hpp"

#include "2D/SpriteComponent.hpp"
#include "2D/MovementComponent.hpp"
#include "2D/AnimationComponent.hpp"
#include "TransformComponent.hpp"

namespace Rvl
{
    void Sprite2DSystem(const std::vector<Entity>& entities)
    {
        for (auto entity : entities)
        {
            if (entity.HasComponent<SpriteComponent>())
            {
                RVL_ASSERT(entity.HasComponent<TransformComponent>(), "entity with sprite component doesn't have transform component");

                auto spriteComponent = entity.GetComponent<SpriteComponent>();
                if (spriteComponent.GetFixedScale())
                {
                    entity.GetComponent<TransformComponent>().Scale = glm::vec3(spriteComponent.GetCurrentScale(), 0.f);
                }
            } 
        }
    }

    void Movement2DSystem(const std::vector<Entity>& entities)
    {
        for (auto entity : entities)
        {
            if (entity.HasComponent<MovementComponent>())
            {
                RVL_ASSERT(entity.HasComponent<TransformComponent>(), "entity with movement component doesn't have transform component");
                auto& movement = entity.GetComponent<MovementComponent>();

                movement.Update();
                entity.GetComponent<TransformComponent>().Position += glm::vec3(movement.GetVelocity(), 0.0) * (float)Time::DeltaTime();
            }
        }
    }

    void Animation2DSystem(const std::vector<Entity>& entities)
    {
        for (auto entity : entities)
        {
            if (entity.HasComponent<AnimationComponent>())
            {
                RVL_ASSERT(entity.HasComponent<SpriteComponent>(), "entity with animation component doesn't have sprite component");

                glm::vec4 subtextureData = entity.GetComponent<AnimationComponent>().GetSubTextureData();
                entity.GetComponent<SpriteComponent>().SetSubTexture(subtextureData.x, subtextureData.y, subtextureData.z, subtextureData.w);
            }
        }
    }
}
