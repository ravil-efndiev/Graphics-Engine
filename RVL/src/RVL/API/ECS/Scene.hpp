#pragma once

#include <entt/entt.hpp>
#include <Core/Core.hpp>
#include <Events/Events.hpp>
#include "Behaviour.hpp"
#include "Systems/System.hpp"

namespace Rvl
{
    class GLShaderProgram;
    class Entity;
    struct EntityData;

    struct EntityHasher
    {
        std::size_t operator()(const Entity& k) const;
    };

    class Scene
    {
    public:
        Scene();
        ~Scene();

        Entity NewEntity();
        Entity NewEntity(const glm::vec3& position);
        Entity NewEntity(const std::string& name);
        Entity NewEntity(const std::string& name, const glm::vec3& position);

        void RemoveEntity(Entity entity);

        Scene& AddSystem(const System& system);
        void AddBehaviour(Behaviour* behaviour);

        void Start();
        void Update();

        void OnEvent(Event* event);

        std::vector<Entity> GetEntities() const;

        void AddChild(Entity parent, Entity child);
        void RemoveChild(Entity parent, Entity child);
        EntityData& GetEntityData(Entity entity);

        friend class Entity;
        friend class HierarchyWindow;
        friend class SceneSerializer;

    private:
        entt::registry _registry;
        
        std::vector<Behaviour*> _behaviours;
        std::vector<Entity> _entities;
        std::vector<System> _systems;
        std::unordered_map<Entity, EntityData, EntityHasher> _entitiesData;
    };
}

