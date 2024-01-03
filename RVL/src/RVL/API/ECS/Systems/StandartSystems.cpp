#include "StandartSystems.hpp"

#include "2D/Sprite.hpp"
#include "2D/Movement2D.hpp"
#include "2D/Animator2D.hpp"
#include "2D/ParticleEmitter.hpp"
#include "2D/TileMap.hpp"
#include "3D/Material.hpp"
#include "3D/DirectionalLight.hpp"
#include "3D/Model.hpp"
#include "3D/PointLight.hpp"
#include "General/Transform.hpp"

#include <Rendering/OpenGL/GLShaderProgram.hpp>
#include <Rendering/Renderer/ModelLoader.hpp>

namespace Rvl
{
    static int pointLightIndex = 0;

    void TransformSystem(const std::vector<Entity>& entities)
    {
        for (auto entity : entities)
        {
            if (!entity.Has<Transform>())
                continue;
            
            EntityData& data = entity.GetData();
            
            if (data.Children.size() > 0)
            {
                auto tf = entity.Get<Transform>();

                if (!(tf == data.LastTransformValue))
                {
                    for (auto child : data.Children)
                    {
                        child.Get<Transform>().Position += (tf.Position - data.LastTransformValue.Position);
                        child.Get<Transform>().Rotation += (tf.Rotation - data.LastTransformValue.Rotation);
                        child.Get<Transform>().Scale    += (tf.Scale - data.LastTransformValue.Scale);
                    }
                }

                data.LastTransformValue = tf;
            }
        }   
    }

    void SpriteSystem(const std::vector<Entity>& entities)
    {
        for (auto entity : entities)
        {
            if (!entity.Has<Sprite>() || entity.Has<Model>() || entity.GetData().IsInstance)
                continue;

            RVL_ASSERT(entity.Has<Transform>(), "entity with sprite component doesn't have transform component");

            auto& sprite = entity.Get<Sprite>();
            if (sprite.UseFixedScale && sprite.Subtexture)
            {
                float ratio = sprite.Subtexture->GetWidth() / sprite.Subtexture->GetHeight();
                glm::vec2 scale = glm::vec2(ratio * sprite.FixedScale, sprite.FixedScale);
                entity.Get<Transform>().Scale = glm::vec3(scale, 0.f);
            }
        }
    }

    void Movement2DSystem(const std::vector<Entity>& entities)
    {
        for (auto entity : entities)
        {
            if (!entity.Has<Movement2D>() || entity.GetData().IsInstance)
                continue;

            RVL_ASSERT(entity.Has<Transform>(), "entity with movement component doesn't have transform component");
            auto& movement = entity.Get<Movement2D>();

            movement.Update();
            entity.Get<Transform>().Position += glm::vec3(movement.GetVelocity(), 0.0) * (float)Time::DeltaTime();
        }
    }

    void Animation2DSystem(const std::vector<Entity>& entities)
    {
        for (auto entity : entities)
        {
            if (!entity.Has<Animator2D>() || entity.GetData().IsInstance)
                continue;

            RVL_ASSERT(entity.Has<Sprite>(), "entity with animation component doesn't have a sprite component");

            glm::vec4 subtextureData = entity.Get<Animator2D>().GetSubTextureData();
            entity.Get<Sprite>().SetSubTexture(subtextureData.x, subtextureData.y, subtextureData.z, subtextureData.w);
        }
    }

    void MaterialSystem(const std::vector<Entity>& entities)
    {
        for (auto entity : entities)
        {
            if (!entity.Has<Material>() || entity.GetData().IsInstance)
                continue;

            auto& material = entity.Get<Material>();

            if (material.ProcessLightSources)
            {
                int index = 0;
                for (auto entity2 : entities)
                {
                    RVL_ASSERT(!(entity2.Has<DirectionalLight>() && entity2.Has<PointLight>()),
                        "Entity has multiple light components interfiering with each other");

                    if (entity2.Has<DirectionalLight>())
                    {
                        RVL_ASSERT(entity2.Has<Transform>(), "Directional light doesn't have transform component");
                        
                        auto light = entity2.Get<DirectionalLight>();
                        auto lightTf = entity2.Get<Transform>();

                        material.SetUniform("u_DirectionalLight.ambient",  light.Ambient);
                        material.SetUniform("u_DirectionalLight.diffuse",  light.Color * light.Intensity); 
                        material.SetUniform("u_DirectionalLight.specular", light.Specular); 
                        material.SetUniform("u_DirectionalLight.direction", lightTf.Rotation); 
                    }

                    if (entity2.Has<PointLight>())
                    {
                        RVL_ASSERT(entity2.Has<Transform>(), "Point light doesn't have transform component");

                        auto light = entity2.Get<PointLight>();
                        auto lightTf = entity2.Get<Transform>();

                        material.SetUniform("u_PointLight[" + std::to_string(index) + "].diffuse",   light.Color * light.Intensity); 
                        material.SetUniform("u_PointLight[" + std::to_string(index) + "].specular",  light.Specular); 
                        material.SetUniform("u_PointLight[" + std::to_string(index) + "].position",  lightTf.Position); 
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

    void ModelLoaderSystem(const std::vector<Entity>& entities)
    {
        for (auto entity : entities)
        {
            if (!entity.Has<Model>() || entity.GetData().IsInstance)
                continue;
            
            auto& model = entity.Get<Model>();
            
            if (model._load) 
            {
                ModelLoader loader (model.Path);
                loader.LoadModel();

                model.Meshes = loader.GetMeshes();
                auto mat = loader.GetMaterial();

                if (!entity.Has<Material>())
                {
                    entity.Add<Material>(mat.Shader, mat.Ambient, mat.Shininess, mat.Textures, mat.Diffuse, mat.Specular, mat.UseTexture);
                }
                else
                {
                    auto& mat2 = entity.Get<Material>();
                    if (mat2.Textures.empty() && mat2.UseTexture)
                        mat2.Textures = mat.Textures;
                }
                model._load = false;
            }
        }
    }

    void ParticleSystem(const std::vector<Entity>& entities)
    {
        for (auto entity : entities)
        {
            if (!entity.Has<ParticleEmitter>() || entity.GetData().IsInstance)
                continue;

            auto& emitter = entity.Get<ParticleEmitter>();

            for (auto& particle : emitter.Particles)
            {
                if (!particle.Active)
                    continue;
                
                if (particle.LifeRemaining <= 0.f)
                {
                    particle.Active = false;
                    continue;
                }

                particle.LifeRemaining -= Time::DeltaTime();
                particle.Position += particle.Velocity * (float)Time::DeltaTime();
                particle.Rotation += 0.01f * Time::DeltaTime();
            }
        }
    }

}
