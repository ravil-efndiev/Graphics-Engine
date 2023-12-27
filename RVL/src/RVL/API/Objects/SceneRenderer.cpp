#include "SceneRenderer.hpp"
#include <Core/App.hpp>
#include <API/ECS/Entity.hpp>
#include <API/ECS/2D/Sprite.hpp>
#include <API/ECS/2D/TileMap.hpp>
#include <API/ECS/3D/Model.hpp>
#include <Rendering/OpenGL/GLTexture.hpp>
#include <Rendering/Renderer/Renderer.hpp>
#include <Rendering/Renderer/Renderer3D.hpp>
#include <Rendering/Renderer/RenderCommand.hpp>

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

        for (Entity entity : entities)
        {
            if (entity.Has<Model>())
                DrawModel(entity, camera->GetCamera()->GetPosition());   

            if (entity.Has<Sprite>())
                DrawSprite(entity);   
            
            if (entity.Has<TileMap>())
                DrawTileMap(entity);  
        }
    }

    void SceneRenderer::DrawSprite(Entity entity)
    {
        RVL_ASSERT((entity.Has<Sprite>() && entity.Has<Transform>()), "entity passed into DrawSprite function doesn't have Sprite Component");

        auto sprite = entity.Get<Sprite>();
        auto transformCompoent = entity.Get<Transform>();
        
        if (!sprite.UseTexture)
            Renderer::DrawRect((Transform)transformCompoent, sprite.Color);

        else if (sprite.UseTexture && sprite.Texture)
            Renderer::DrawRect((Transform)transformCompoent, sprite.Subtexture, sprite.Color);
    }
    
    void SceneRenderer::DrawTileMap(Entity entity)
    {
        RVL_ASSERT((entity.Has<TileMap>() && entity.Has<Transform>()), "entity passed into DrawTileMap function doesn't have TileMap Component");

        auto tilemap = entity.Get<TileMap>();
        auto transform = entity.Get<Transform>();
        
        for (auto& tile : tilemap.MapTiles)
        {
            Renderer::DrawRect({tile.GetRelativePosition() + transform.Position, transform.Rotation, tile.GetScale()}, tile.GetSubtexture());
        }
    }

    void SceneRenderer::DrawModel(Entity entity, const glm::vec3& cameraPos)
    {
        RVL_ASSERT((entity.Has<Model>()), "entity passed into DrawModel function doesn't have Model Component");
        RVL_ASSERT((entity.Has<Transform>()), "entity passed into DrawModel function doesn't have Transform Component");
        RVL_ASSERT((entity.Has<Material>()), "entity passed into DrawModel function doesn't have Material Component");

        auto  meshes = entity.Get<Model>().Meshes;
        auto  transform = entity.Get<Transform>();
        auto& material = entity.Get<Material>();

        material.SetUniform("u_ViewPos", cameraPos);

        for (auto& mesh : meshes)
        {
            Renderer3D::SubmitMesh(mesh, material, (Transform)transform);
        }
    }

}
