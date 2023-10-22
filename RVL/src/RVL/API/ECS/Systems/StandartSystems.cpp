#include "StandartSystems.hpp"

#include "2D/SpriteComponent.hpp"
#include "2D/MovementComponent.hpp"
#include "2D/AnimationComponent.hpp"
#include "3D/MaterialComponent.hpp"
#include "3D/DirectionalLightComponent.hpp"
#include "3D/PointLightComponent.hpp"
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

    void MaterialSystem(const std::vector<Entity>& entities)
    {
        for (auto entity : entities)
        {
            if (!entity.HasComponent<MaterialComponent>())
                continue;

            auto& material = entity.GetComponent<MaterialComponent>();

            material.Update();

            if (material.ShouldProcessLightSources())
            {
                for (auto entity2 : entities)
                {
                    RVL_ASSERT(!(entity2.HasComponent<DirectionalLightComponent>() && entity2.HasComponent<PointLightComponent>()),
                        "Entity has multiple light components interfiering with each other");

                    if (entity2.HasComponent<DirectionalLightComponent>())
                    {
                        RVL_ASSERT(entity2.HasComponent<TransformComponent>(), "Directional light doesn't have transform component");
                        
                        auto light = entity2.GetComponent<DirectionalLightComponent>();
                        auto lightTf = entity2.GetComponent<TransformComponent>();

                        material.Set("u_DirectionalLight.ambient",  light.GetAmbient());
                        material.Set("u_DirectionalLight.diffuse",  light.GetDiffuse()); 
                        material.Set("u_DirectionalLight.specular", light.GetSpecular()); 
                        material.Set("u_DirectionalLight.direction", lightTf.Rotation()); 
                    }

                    if (entity2.HasComponent<PointLightComponent>())
                    {
                        RVL_ASSERT(entity2.HasComponent<TransformComponent>(), "Point light doesn't have transform component");
                        
                        auto light = entity2.GetComponent<PointLightComponent>();
                        auto lightTf = entity2.GetComponent<TransformComponent>();

                        material.Set("u_PointLight.ambient",  light.GetAmbient());
                        material.Set("u_PointLight.diffuse",  light.GetDiffuse()); 
                        material.Set("u_PointLight.specular", light.GetSpecular()); 
                        material.Set("u_PointLight.position", lightTf.Position()); 
                        material.Set("u_PointLight.constant", light.Constant);
                        material.Set("u_PointLight.linear",   light.GetLinear());
                        material.Set("u_PointLight.quadratic", light.GetQuadratic());	
                    }
                }
            }
        
        }
    }
}
