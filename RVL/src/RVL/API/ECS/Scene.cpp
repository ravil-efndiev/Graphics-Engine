#include "Scene.hpp"
#include "Entity.hpp"
#include "General/Transform.hpp"
#include "2D/Sprite.hpp"
#include "2D/TileMap.hpp"
#include "3D/Model.hpp"
#include "3D/Material.hpp"
#include "General/Identifier.hpp"

#include <Rendering/Renderer/Renderer.hpp>
#include <Rendering/Renderer/Renderer3D.hpp>

#include "Systems/StandartSystems.hpp"

namespace Rvl
{
    static int entityNum = 0;

    Scene::Scene() 
    {
        AddSystem(Movement2DSystem);
        AddSystem(Animation2DSystem);
        AddSystem(MaterialSystem);
        AddSystem(LightSystem);
        AddSystem(ModelLoaderSystem);
    }

    Scene::~Scene() {}
    
    Entity Scene::NewEntity()
    {
        Entity entity (this, _registry.create());
        entityNum++;
        entity.Add<Identifier>("Entity" + std::to_string(entityNum));
        entity.Add<Transform>(glm::vec3(0.f), glm::vec3(0.f), glm::vec3(1.f, 1.f, 1.f));
        _entities.push_back(entity);
        return entity;
    }

    Entity Scene::NewEntity(const glm::vec3& position)
    {
       Entity entity (this, _registry.create());
        entityNum++;
        entity.Add<Identifier>("Entity" + std::to_string(entityNum));
        entity.Add<Transform>(position, glm::vec3(0.f), glm::vec3(1.f, 1.f, 1.f));
        _entities.push_back(entity);
        return entity;
    }

    Entity Scene::NewEntity(const std::string& name)
    {
        Entity entity (this, _registry.create());
        entityNum++;
        entity.Add<Identifier>(name);
        entity.Add<Transform>(glm::vec3(0.f), glm::vec3(0.f), glm::vec3(1.f, 1.f, 1.f));
        _entities.push_back(entity);
        return entity;
    }

    Entity Scene::NewEntity(const std::string& name, const glm::vec3& position)
    {
        Entity entity (this, _registry.create());
        entityNum++;
        entity.Add<Identifier>(name);
        entity.Add<Transform>(position, glm::vec3(0.f), glm::vec3(1.f, 1.f, 1.f));
        _entities.push_back(entity);
        return entity;
    }

    void Scene::RemoveEntity(Entity entity)
    {
        _entities.erase(std::remove(_entities.begin(), _entities.end(), entity));
        _registry.destroy(entity.GetId());
    }

    void Scene::AddSystem(const System& system)
    {
        _systems.push_back(system);
    }
    
    void Scene::DrawSprite(Entity entity)
    {
        RVL_ASSERT((entity.Has<Sprite>() && entity.Has<Transform>()), "entity passed into DrawSprite function doesn't have Sprite Component");

        auto spriteCompoent = entity.Get<Sprite>();
        auto transformCompoent = entity.Get<Transform>();
        
        if (spriteCompoent.Drawtype == Sprite::DrawType::Color)
            Renderer::DrawRect((Transform)transformCompoent, spriteCompoent.Color);

        else if (spriteCompoent.Drawtype == Sprite::DrawType::Texture)
        {
            if (spriteCompoent.UseColorAsTint)
               Renderer::DrawRect((Transform)transformCompoent, spriteCompoent.Subtexture, spriteCompoent.Color);

            else
               Renderer::DrawRect((Transform)transformCompoent, spriteCompoent.Subtexture);
        }
    }
    
    void Scene::DrawTileMap(Entity entity)
    {
        RVL_ASSERT((entity.Has<TileMap>()), "entity passed into DrawTileMap function doesn't have TileMap Component");

        auto tilemap = entity.Get<TileMap>();
        
        for (auto& tile : tilemap.GetTiles())
        {
            Renderer::DrawRect(tile.GetTransform(), tile.GetSubtexture());
        }
    }

    void Scene::DrawModel(Entity entity)
    {
        RVL_ASSERT((entity.Has<Model>()), "entity passed into DrawModel function doesn't have Model Component");
        RVL_ASSERT((entity.Has<Transform>()), "entity passed into DrawModel function doesn't have Transform Component");
        RVL_ASSERT((entity.Has<Material>()), "entity passed into DrawModel function doesn't have Material Component");

        auto meshes = entity.Get<Model>().Meshes;
        auto transform = entity.Get<Transform>();
        auto material = entity.Get<Material>();

        for (auto& mesh : meshes)
        {
            Renderer3D::SubmitMesh(mesh, material, (Transform)transform);
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
