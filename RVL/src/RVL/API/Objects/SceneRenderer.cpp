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
#include <Rendering/Renderer/RenderCommand.hpp>
#include "Math/Math.hpp"

namespace Rvl
{
    static std::vector<Entity> prevEntities;

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

        // drawing particle emitters in a separate draw call to change blend and depth values
        glDepthFunc(GL_LEQUAL);
        glDepthMask(GL_FALSE);
        for (Entity entity : entities)
        {
            if (entity.Has<ParticleEmitter>())
                DrawParticles(entity);  
        }
        Renderer::FlushAndReset();
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glDepthFunc(GL_LESS);
        glDepthMask(GL_TRUE);

        for (Entity entity : entities)
        {
            if (entity.Has<Sprite>())
                DrawSprite(entity);   
            
            if (entity.Has<TileMap>())
                DrawTileMap(entity);  

            if (entity.Has<Model>())
                DrawModel(entity, camera->GetCamera()->GetPosition());   
        }

    }

    void SceneRenderer::DrawSprite(Entity entity)
    {
        RVL_ASSERT((entity.Has<Sprite>() && entity.Has<Transform>()), "SceneRenderer: entity passed into DrawSprite function doesn't have Sprite or Transform Component");

        auto sprite = entity.Get<Sprite>();
        auto transformCompoent = entity.Get<Transform>();
        
        if (!sprite.UseTexture)
            Renderer::DrawRect((Transform)transformCompoent, sprite.Color);

        else if (sprite.UseTexture && sprite.Texture)
            Renderer::DrawRect((Transform)transformCompoent, sprite.Subtexture, sprite.Color);
    }
    
    void SceneRenderer::DrawTileMap(Entity entity)
    {
        RVL_ASSERT((entity.Has<TileMap>() && entity.Has<Transform>()), "SceneRenderer: entity passed into DrawTileMap function doesn't have TileMap or Transform Component");

        auto tilemap = entity.Get<TileMap>();
        auto transform = entity.Get<Transform>();
        
        for (auto& tile : tilemap.MapTiles)
        {
            Renderer::DrawRect({tile.GetRelativePosition() + transform.Position, transform.Rotation, tile.GetScale()}, tile.GetSubtexture());
        }
    }

    void SceneRenderer::DrawModel(Entity entity, const glm::vec3& cameraPos)
    {
        RVL_ASSERT((entity.Has<Model>()), "SceneRenderer: entity passed into DrawModel function doesn't have Model Component");
        RVL_ASSERT((entity.Has<Transform>()), "SceneRenderer: entity passed into DrawModel function doesn't have Transform Component");
        RVL_ASSERT((entity.Has<Material>()), "SceneRenderer: entity passed into DrawModel function doesn't have Material Component");

        auto  meshes = entity.Get<Model>().Meshes;
        auto  transform = entity.Get<Transform>();
        auto& material = entity.Get<Material>();

        material.SetUniform("u_ViewPos", cameraPos);

        for (auto& mesh : meshes)
        {
            Renderer3D::SubmitMesh(mesh, material, (Transform)transform);
        }
    }

    void SceneRenderer::DrawParticles(Entity entity)
    {        
        RVL_ASSERT((entity.Has<Transform>()), "SceneRenderer: entity passed into DrawParticles function doesn't have Transform Component");
        RVL_ASSERT((entity.Has<ParticleEmitter>()), "SceneRenderer: entity passed into DrawParticles function doesn't have ParticleEmitter Component");

        auto& emitter = entity.Get<ParticleEmitter>();
        glm::vec3 pos = entity.Get<Transform>().Position;

        if (emitter.AdditiveBlend)
            glBlendFunc(GL_SRC_ALPHA, GL_ONE);
        else
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        for (auto& particle : emitter.Particles)
        {
            if (!particle.Active)
                continue;

            float life = particle.LifeRemaining / particle.LifeTime;
            glm::vec4 color = Math::Lerp(particle.ColorEnd, particle.ColorStart, life);
            color.a *= life;

            float size = Math::Lerp(particle.SizeEnd, particle.SizeStart, life);

            if (particle.Texture && particle.UseTexture)
                Renderer::DrawRect({particle.Position + pos, {0.f, 0.f, particle.Rotation}, {size, size, 0.f}}, particle.Texture, color);
            else
                Renderer::DrawRect({particle.Position + pos, {0.f, 0.f, particle.Rotation}, {size, size, 0.f}}, color);

        }
    }
}
