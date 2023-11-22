#include "StandartSystems.hpp"

#include "2D/SpriteComponent.hpp"
#include "2D/MovementComponent.hpp"
#include "2D/AnimationComponent.hpp"
#include "3D/MaterialComponent.hpp"
#include "3D/DirectionalLightComponent.hpp"
#include "3D/ModelComponent.hpp"
#include "3D/PointLightComponent.hpp"
#include "General/TransformComponent.hpp"

#include <Rendering/OpenGL/GLShaderProgram.hpp>

namespace Rvl
{
    static int pointLightIndex = 0;

    void Sprite2DSystem(const std::vector<Entity>& entities)
    {
        for (auto entity : entities)
        {
            if (!entity.Has<SpriteComponent>() || entity.Has<ModelComponent>())
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

            material.SetUniform("u_Material.diffuse",  material.Diffuse);
            material.SetUniform("u_Material.specular", material.Specular);
            material.SetUniform("u_Material.ambient",  material.Ambient);
            material.SetUniform("u_Material.shininess", material.Shininess);

            if (material.ProcessLightSources)
            {
                int index = 0;
                for (auto entity2 : entities)
                {
                    RVL_ASSERT(!(entity2.Has<DirectionalLightComponent>() && entity2.Has<PointLightComponent>()),
                        "Entity has multiple light components interfiering with each other");

                    if (entity2.Has<DirectionalLightComponent>())
                    {
                        RVL_ASSERT(entity2.Has<TransformComponent>(), "Directional light doesn't have transform component");
                        
                        auto light = entity2.Get<DirectionalLightComponent>();
                        auto lightTf = entity2.Get<TransformComponent>();

                        material.SetUniform("u_DirectionalLight.ambient",  light.Ambient);
                        material.SetUniform("u_DirectionalLight.diffuse",  light.Diffuse); 
                        material.SetUniform("u_DirectionalLight.specular", light.Specular); 
                        material.SetUniform("u_DirectionalLight.direction", lightTf.Rotation()); 
                    }

                    if (entity2.Has<PointLightComponent>())
                    {
                        RVL_ASSERT(entity2.Has<TransformComponent>(), "Point light doesn't have transform component");

                        auto light = entity2.Get<PointLightComponent>();
                        auto lightTf = entity2.Get<TransformComponent>();

                        material.SetUniform("u_PointLight[" + std::to_string(index) + "].ambient",   light.Ambient);
                        material.SetUniform("u_PointLight[" + std::to_string(index) + "].diffuse",   light.Diffuse); 
                        material.SetUniform("u_PointLight[" + std::to_string(index) + "].specular",  light.Specular); 
                        material.SetUniform("u_PointLight[" + std::to_string(index) + "].position",  lightTf.Position()); 
                        material.SetUniform("u_PointLight[" + std::to_string(index) + "].constant",  light.Constant);
                        material.SetUniform("u_PointLight[" + std::to_string(index) + "].linear",    light.Linear);
                        material.SetUniform("u_PointLight[" + std::to_string(index) + "].quadratic", light.Quadratic);	
                        material.SetUniform("u_PointLight[" + std::to_string(index) + "].none", 0.f);	
                        index++;
                    }
                }
                material.SetUniform("u_LightsCount", index);
            }
        
        }
    }

    void LightSystem(const std::vector<Entity>& entities)
    {
        for (auto entity : entities)
        {
            if (entity.Has<DirectionalLightComponent>())
            {
                auto& dl = entity.Get<DirectionalLightComponent>();

                dl.Diffuse = dl.Color * dl.Intensity;
            }

            if (entity.Has<PointLightComponent>())
            {
                auto& pl = entity.Get<PointLightComponent>();

                pl.Diffuse = pl.Color * pl.Intensity;
            }

        }
    }
}
