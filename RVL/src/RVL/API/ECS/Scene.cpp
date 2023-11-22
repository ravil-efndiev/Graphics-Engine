#include "Scene.hpp"
#include "Entity.hpp"
#include "General/TransformComponent.hpp"
#include "2D/SpriteComponent.hpp"
#include "2D/TileMapComponent.hpp"
#include "3D/ModelComponent.hpp"
#include "3D/MaterialComponent.hpp"
#include "General/IdentifierComponent.hpp"

#include <Rendering/Renderer/Renderer.hpp>
#include <Rendering/Renderer/Renderer3D.hpp>

#include "Systems/StandartSystems.hpp"

namespace Rvl
{
    static int entityNum = 0;

    Scene::Scene() 
    {
        AddSystem(Sprite2DSystem);
        AddSystem(Movement2DSystem);
        AddSystem(Animation2DSystem);
        AddSystem(MaterialSystem);
        AddSystem(LightSystem);
    }

    Scene::~Scene() {}
    
    Entity Scene::NewEntity()
    {
        Entity entity (this, _registry.create());
        entityNum++;
        entity.Add<IdentifierComponent>("Entity" + std::to_string(entityNum));
        entity.Add<TransformComponent>(glm::vec3(0.f), glm::vec3(0.f), glm::vec3(1.f, 1.f, 1.f));
        _entities.push_back(entity);
        return entity;
    }

    Entity Scene::NewEntity(const glm::vec3& position)
    {
       Entity entity (this, _registry.create());
        entityNum++;
        entity.Add<IdentifierComponent>("Entity" + std::to_string(entityNum));
        entity.Add<TransformComponent>(position, glm::vec3(0.f), glm::vec3(1.f, 1.f, 1.f));
        _entities.push_back(entity);
        return entity;
    }

    Entity Scene::NewEntity(const std::string& name)
    {
        Entity entity (this, _registry.create());
        entityNum++;
        entity.Add<IdentifierComponent>(name);
        entity.Add<TransformComponent>(glm::vec3(0.f), glm::vec3(0.f), glm::vec3(1.f, 1.f, 1.f));
        _entities.push_back(entity);
        return entity;
    }

    Entity Scene::NewEntity(const std::string& name, const glm::vec3& position)
    {
        Entity entity (this, _registry.create());
        entityNum++;
        entity.Add<IdentifierComponent>(name);
        entity.Add<TransformComponent>(position, glm::vec3(0.f), glm::vec3(1.f, 1.f, 1.f));
        _entities.push_back(entity);
        return entity;
    }

    void Scene::AddSystem(const System& system)
    {
        _systems.push_back(system);
    }
    
    void Scene::DrawSprite(Entity entity)
    {
        RVL_ASSERT((entity.Has<SpriteComponent>() && entity.Has<TransformComponent>()), "entity passed into DrawSprite function doesn't have Sprite Component");

        auto spriteCompoent = entity.Get<SpriteComponent>();
        auto transformCompoent = entity.Get<TransformComponent>();
        
        if (spriteCompoent.Drawtype == SpriteComponent::DrawType::Color)
            Renderer::DrawRect((Transform)transformCompoent, spriteCompoent.Color);

        else if (spriteCompoent.Drawtype == SpriteComponent::DrawType::Texture)
        {
            if (spriteCompoent.UseColorAsTint)
               Renderer::DrawRect((Transform)transformCompoent, spriteCompoent.Subtexture, spriteCompoent.Color);

            else
               Renderer::DrawRect((Transform)transformCompoent, spriteCompoent.Subtexture);
        }
    }
    
    void Scene::DrawTileMap(Entity entity)
    {
        RVL_ASSERT((entity.Has<TileMapComponent>()), "entity passed into DrawTileMap function doesn't have TileMap Component");

        auto tileMapComponent = entity.Get<TileMapComponent>();
        
        for (auto& tile : tileMapComponent.GetTiles())
        {
            Renderer::DrawRect(tile.GetTransform(), tile.GetSubtexture());
        }
    }

    void Scene::DrawModel(Entity entity)
    {
        RVL_ASSERT((entity.Has<ModelComponent>()), "entity passed into DrawModel function doesn't have Model Component");
        RVL_ASSERT((entity.Has<TransformComponent>()), "entity passed into DrawModel function doesn't have Transform Component");
        RVL_ASSERT((entity.Has<MaterialComponent>()), "entity passed into DrawModel function doesn't have Material Component");

        auto meshes = entity.Get<ModelComponent>().GetMeshes();
        auto transform = entity.Get<TransformComponent>();
        auto material = entity.Get<MaterialComponent>();

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
    
    std::vector<Entity> Scene::GetEntities() const
    {
        return _entities;
    }
}
