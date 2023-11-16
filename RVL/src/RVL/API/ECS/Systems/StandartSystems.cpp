#include "StandartSystems.hpp"

#include "2D/SpriteComponent.hpp"
#include "2D/MovementComponent.hpp"
#include "2D/AnimationComponent.hpp"
#include "3D/MaterialComponent.hpp"
#include "3D/DirectionalLightComponent.hpp"
#include "3D/PointLightComponent.hpp"
#include "General/TransformComponent.hpp"

namespace Rvl
{
    void Sprite2DSystem(const std::vector<Entity>& entities)
    {
        for (auto entity : entities)
        {
            if (!entity.Has<SpriteComponent>())
                continue;

            RVL_ASSERT(entity.Has<TransformComponent>(), "entity with sprite component doesn't have transform component");

            auto spriteComponent = entity.Get<SpriteComponent>();
            if (spriteComponent.UseFixedScale)
            {
                entity.Get<TransformComponent>().Scale = glm::vec3(spriteComponent.ScaleVec2, 0.f);
            }
        }
    }

    void Movement2DSystem(const std::vector<Entity>& entities)
    {
        for (auto entity : entities)
        {
            if (!entity.Has<MovementComponent>())
                continue;

            RVL_ASSERT(entity.Has<TransformComponent>(), "entity with movement component doesn't have transform component");
            auto& movement = entity.Get<MovementComponent>();

            movement.Update();
            entity.Get<TransformComponent>().Position += glm::vec3(movement.GetVelocity(), 0.0) * (float)Time::DeltaTime();
        }
    }

    void Animation2DSystem(const std::vector<Entity>& entities)
    {
        for (auto entity : entities)
        {
            if (!entity.Has<AnimationComponent>())
                continue;

            RVL_ASSERT(entity.Has<SpriteComponent>(), "entity with animation component doesn't have sprite component");

            glm::vec4 subtextureData = entity.Get<AnimationComponent>().GetSubTextureData();
            entity.Get<SpriteComponent>().SetSubTexture(subtextureData.x, subtextureData.y, subtextureData.z, subtextureData.w);
        }
    }

    void MaterialSystem(const std::vector<Entity>& entities)
    {
        for (auto entity : entities)
        {
            if (!entity.Has<MaterialComponent>())
                continue;

            auto& material = entity.Get<MaterialComponent>();

            material.Update();

            if (material.ShouldProcessLightSources())
            {
                for (auto entity2 : entities)
                {
                    RVL_ASSERT(!(entity2.Has<DirectionalLightComponent>() && entity2.Has<PointLightComponent>()),
                        "Entity has multiple light components interfiering with each other");

                    if (entity2.Has<DirectionalLightComponent>())
                    {
                        RVL_ASSERT(entity2.Has<TransformComponent>(), "Directional light doesn't have transform component");
                        
                        auto light = entity2.Get<DirectionalLightComponent>();
                        auto lightTf = entity2.Get<TransformComponent>();

                        material.Set("u_DirectionalLight.ambient",  light.Ambient);
                        material.Set("u_DirectionalLight.diffuse",  light.Diffuse); 
                        material.Set("u_DirectionalLight.specular", light.Specular); 
                        material.Set("u_DirectionalLight.direction", lightTf.Rotation()); 
                    }

                    if (entity2.Has<PointLightComponent>())
                    {
                        RVL_ASSERT(entity2.Has<TransformComponent>(), "Point light doesn't have transform component");
                        
                        auto light = entity2.Get<PointLightComponent>();
                        auto lightTf = entity2.Get<TransformComponent>();

                        material.Set("u_PointLight.ambient",   light.Ambient);
                        material.Set("u_PointLight.diffuse",   light.Diffuse); 
                        material.Set("u_PointLight.specular",  light.Specular); 
                        material.Set("u_PointLight.position",  lightTf.Position()); 
                        material.Set("u_PointLight.constant",  light.Constant);
                        material.Set("u_PointLight.linear",    light.Linear);
                        material.Set("u_PointLight.quadratic", light.Quadratic);	
                    }
                }
            }
        
        }
    }
}
