#pragma once

#include <entt/entt.hpp>
#include <Core/Core.hpp>
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
        void AddSystem(const System& system);

        void DrawSprite(Entity entity);
        void DrawTileMap(Entity entity);
        void DrawModel(Entity entity, const Ref<GLShaderProgram>& shader);

        void AddBehaviour(Behaviour* behaviour);

        void StartBehaviours();
        void UpdateBehaviours();

        friend class Entity;

    private:
        entt::registry _registry;
        
        std::vector<Behaviour*> _behaviours;
        std::vector<Entity> _entities;
        std::vector<System> _systems;
    };
}

