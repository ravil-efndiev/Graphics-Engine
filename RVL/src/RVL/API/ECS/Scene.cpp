#include "Scene.hpp"
#include "Entity.hpp"
#include "TransformComponent.hpp"
#include "2D/SpriteComponent.hpp"
#include "2D/TileMapComponent.hpp"
#include "3D/ModelComponent.hpp"
#include "3D/MaterialComponent.hpp"

#include <Rendering/Renderer/Renderer.hpp>
#include <Rendering/Renderer/Renderer3D.hpp>

#include "Systems/StandartSystems.hpp"

namespace Rvl
{
    Scene::Scene() 
    {
        AddSystem(Sprite2DSystem);
        AddSystem(Movement2DSystem);
        AddSystem(Animation2DSystem);
        AddSystem(MaterialSystem);
    }

    Scene::~Scene() {}
    
    Entity Scene::NewEntity()
    {
        Entity entity (this, _registry.create());
        entity.AddComponent<TransformComponent>(glm::vec3(0.f), glm::vec3(0.f), glm::vec3(1.f, 1.f, 1.f));
        _entities.push_back(entity);
        return entity;
    }

    void Scene::AddSystem(const System& system)
    {
        _systems.push_back(system);
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

    void Scene::DrawModel(Entity entity)
    {
        RVL_ASSERT((entity.HasComponent<ModelComponent>()), "entity passed into DrawModel function doesn't have Model Component");
        RVL_ASSERT((entity.HasComponent<TransformComponent>()), "entity passed into DrawModel function doesn't have Transform Component");
        RVL_ASSERT((entity.HasComponent<MaterialComponent>()), "entity passed into DrawModel function doesn't have Material Component");

        auto meshes = entity.GetComponent<ModelComponent>().GetMeshes();
        auto transform = entity.GetComponent<TransformComponent>();
        auto material = entity.GetComponent<MaterialComponent>();

        for (auto& mesh : meshes)
        {
            Renderer3D::SubmitMesh(mesh, material.GetShader(), (Transform)transform);
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

        for (auto system : _systems)
        {
            system(_entities);
        }
    }
    
    void Scene::OnEvent(Event* event)
    {
        for (auto behaviour : _behaviours)
        {
            behaviour->OnEvent(event);
        }
    }
}
