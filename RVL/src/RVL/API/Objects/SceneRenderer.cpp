#include "SceneRenderer.hpp"
#include <Core/App.hpp>
#include <API/ECS/Entity.hpp>
#include <API/ECS/2D/Sprite.hpp>
#include <API/ECS/2D/TileMap.hpp>
#include <API/ECS/2D/ParticleEmitter.hpp>
#include <API/ECS/3D/Model.hpp>
#include <Rendering/OpenGL/GLTexture.hpp>
#include <Rendering/Renderer/Renderer.hpp>
#include <Rendering/Renderer/Renderer3D.hpp>
#include <Rendering/Renderer/RenderEntity.hpp>
#include "Math/Math.hpp"

namespace Rvl
{
    static std::vector<Entity> prevEntities;
    RenderType SceneRenderer::_renderType = RenderType::Normal;    

    void SceneRenderer::Render(const Ref<Scene>& scene, const Ref<UserCamera>& camera)
    {
        auto entities = scene->GetEntities();
        if (entities != prevEntities)
        {
            std::sort(entities.begin(), entities.end(), [&](Entity entity1, Entity entity2)
            {   
                return entity1.Get<Transform>().Position.z < entity2.Get<Transform>().Position.z;
            });
        }

        // drawing particle emitters in separate draw calls to change blend and depth values
        // emitters that use additive blending are drawn in another separate draw call
        DrawParticleEmitters(entities);

        for (Entity entity : entities)
        {
            EntityData& data = entity.GetData();
            if (data.IsInstance)
                continue;

            if (entity.Has<Sprite>())
                DrawSprite(entity);   
            
            if (entity.Has<TileMap>())
                DrawTileMap(entity);  

            if (entity.Has<Model>())
                DrawModel(entity, camera->GetCamera()->GetPosition(), data);   
        }
    }

    void SceneRenderer::DrawSprite(Entity entity)
    {
        RVL_ASSERT((entity.Has<Transform>()), "SceneRenderer: entity passed into DrawSprite function doesn't have Sprite or Transform Component");

        auto sprite = entity.Get<Sprite>();
        auto transformCompoent = entity.Get<Transform>();
        
        if (!sprite.UseTexture)
            Renderer::DrawRect((Transform)transformCompoent, sprite.Color);

        else if (sprite.UseTexture && sprite.Texture)
            Renderer::DrawRect((Transform)transformCompoent, sprite.Subtexture, sprite.Color);
    }
    
    void SceneRenderer::DrawTileMap(Entity entity)
    {
        RVL_ASSERT((entity.Has<Transform>()), "SceneRenderer: entity passed into DrawTileMap function doesn't have Transform Component");

        auto tilemap = entity.Get<TileMap>();
        auto transform = entity.Get<Transform>();
        
        for (auto& tile : tilemap.MapTiles)
        {
            Renderer::DrawRect({tile.GetRelativePosition() + transform.Position, transform.Rotation, tile.GetScale()}, tile.GetSubtexture());
        }
    }

    void SceneRenderer::DrawModel(Entity entity, const glm::vec3& cameraPos, EntityData& data)
    {
        RVL_ASSERT((entity.Has<Transform>()), "SceneRenderer: entity passed into DrawModel function doesn't have Transform Component");
        RVL_ASSERT((entity.Has<Material>()), "SceneRenderer: entity passed into DrawModel function doesn't have Material Component");

        auto& model     = entity.Get<Model>();
        auto& material  = entity.Get<Material>();
        auto& transform = entity.Get<Transform>();

        material.SetUniform("u_ViewPos", cameraPos);

        std::vector<Transform> transforms (data.Instances.size() + 1);
        transforms[0] = transform;
        for (int i = 1; i < transforms.size(); i++)
        {  
            transforms[i] = *data.Instances[i - 1];
        }

        RenderEntity re (model.Meshes.data(), model.Meshes.size(), model.RepeatUV, _renderType);
        Renderer3D::SubmitEntityInstanced(re, material, transforms, transforms.size() > data.LastTransformsSize);
        data.LastTransformsSize = transforms.size();
    }

    void SceneRenderer::DrawParticleEmitters(const std::vector<Entity>& entities)
    {
        glDepthFunc(GL_LEQUAL);
        glDepthMask(GL_FALSE);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE);
        for (Entity entity : entities)
        {
            if (entity.Has<ParticleEmitter>())
            {
                RVL_ASSERT((entity.Has<Transform>()), "SceneRenderer: entity passed into DrawParticles function doesn't have Transform Component");
        
                auto& emitter = entity.Get<ParticleEmitter>();
                glm::vec3 pos = entity.Get<Transform>().Position;

                if (!emitter.AdditiveBlend)
                    continue;

                DrawParticles(emitter, pos);
            }
        }

        Renderer::FlushAndReset();
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        
        for (Entity entity : entities)
        {
            if (entity.Has<ParticleEmitter>())
            {
                RVL_ASSERT((entity.Has<Transform>()), "SceneRenderer: entity passed into DrawParticles function doesn't have Transform Component");
        
                auto& emitter = entity.Get<ParticleEmitter>();
                glm::vec3 pos = entity.Get<Transform>().Position;

                if (emitter.AdditiveBlend)
                    continue;

                DrawParticles(emitter, pos);
            }
        }

        Renderer::FlushAndReset();
        glDepthFunc(GL_LESS);
        glDepthMask(GL_TRUE);
    }

    void SceneRenderer::DrawParticles(ParticleEmitter& emitter, const glm::vec3& tfPos)
    {        
        for (auto& particle : emitter.Particles)
        {
            if (!particle.Active)
                continue;

            float life = particle.LifeRemaining / particle.LifeTime;
            glm::vec4 color = Math::Lerp(particle.ColorEnd, particle.ColorStart, life);
            color.a *= life;

            float size = Math::Lerp(particle.SizeEnd, particle.SizeStart, life);

            if (particle.Texture && particle.UseTexture)
                Renderer::DrawRect({particle.Position + tfPos, {0.f, 0.f, particle.Rotation}, {size, size, 0.f}}, particle.Texture, color);
            else
                Renderer::DrawRect({particle.Position + tfPos, {0.f, 0.f, particle.Rotation}, {size, size, 0.f}}, color);
        }
    }

    void SceneRenderer::SetRenderType(RenderType type)
    {
        _renderType = type;
        Renderer::SetRenderType(_renderType);
    }

}
