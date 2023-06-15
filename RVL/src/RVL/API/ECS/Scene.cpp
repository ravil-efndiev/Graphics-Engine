#include "Scene.hpp"
#include "Entity.hpp"
#include "TransformComponent.hpp"
#include "SpriteComponent.hpp"
#include "TileMapComponent.hpp"

#include <Rendering/Renderer/Renderer.hpp>

namespace Rvl
{
    Scene::Scene() {}
    Scene::~Scene() {}
    
    Entity Scene::NewEntity()
    {
        Entity entity (this, _registry.create());
        entity.AddComponent<TransformComponent>(glm::vec3(0.f, 0.f, 0.f), 0.f, glm::vec2(0.f, 0.f));
        return entity;
    }
    
    void Scene::DrawSprite(Entity entity)
    {
        RVL_ASSERT((entity.HasComponent<SpriteComponent>() && entity.HasComponent<TransformComponent>()), "entity passed into DrawSprite function doesn't have Sprite Component");

        auto spriteCompoent = entity.GetComponent<SpriteComponent>();
        auto transformCompoent = entity.GetComponent<TransformComponent>();
        
        if (spriteCompoent.GetDrawType() == SpriteComponent::DrawType::Color)
            Renderer::DrawRect((Transform)transformCompoent, spriteCompoent.GetColor());

        else if (spriteCompoent.GetDrawType() == SpriteComponent::DrawType::Texture)
        {
            if (spriteCompoent.ColorIsTint())
               Renderer::DrawRect((Transform)transformCompoent, spriteCompoent.GetSubTexture(), spriteCompoent.GetColor());

            else
               Renderer::DrawRect((Transform)transformCompoent, spriteCompoent.GetSubTexture());
        }
    }
    
    void Scene::DrawTileMap(Entity entity)
    {
        RVL_ASSERT((entity.HasComponent<TileMapComponent>()), "entity passed into DrawTileMap function doesn't have TileMap Component");

        auto tileMapComponent = entity.GetComponent<TileMapComponent>();
        
        for (auto& tile : tileMapComponent.GetTiles())
        {
            Renderer::DrawRect(tile.GetTransform(), tile.GetSubtexture());
        }
    }

    void Scene::AddBehaviour(Behaviour* behaviour)
    {
        _behaviours.push_back(behaviour);
        
    }

    void Scene::StartBehaviours()
    {
        for (auto behaviour : _behaviours)
        {
            behaviour->Start();
        }
    }
    
    void Scene::UpdateBehaviours()
    {
        for (auto behaviour : _behaviours)
        {
            behaviour->Update();
        }
    }
}
