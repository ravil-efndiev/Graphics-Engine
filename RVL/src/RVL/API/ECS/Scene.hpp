#pragma once

#include <entt/entt.hpp>
#include <Core/Core.hpp>
#include <Events/Events.hpp>
#include "Behaviour.hpp"
#include "Systems/System.hpp"

namespace Rvl
{
    class Entity;
    class GLShaderProgram;

    class Scene
    {
    public:
        Scene();
        ~Scene();

        Entity NewEntity();
        Entity NewEntity(const glm::vec3& position);
        Entity NewEntity(const std::string& name);
        Entity NewEntity(const std::string& name, const glm::vec3& position);

        void AddSystem(const System& system);
        void AddBehaviour(Behaviour* behaviour);

        void DrawSprite(Entity entity);
        void DrawTileMap(Entity entity);
        void DrawModel(Entity entity);

        void StartBehaviours();
        void UpdateBehaviours();

        void OnEvent(Event* event);

        std::vector<Entity> GetEntities() const;

        friend class Entity;
        friend class HierarchyWindow;

    private:
        entt::registry _registry;
        
        std::vector<Behaviour*> _behaviours;
        std::vector<Entity> _entities;
        std::vector<System> _systems;
    };
}

