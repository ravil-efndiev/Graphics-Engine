#pragma once

#include <entt/entt.hpp>
#include <Core/Core.hpp>
#include "Component.hpp"
#include "Behaviour.hpp"

namespace Rvl
{
    class Entity;
    class GLShaderProgram;

    class Scene
    {
    public:
        Scene();
        ~Scene();

        friend class Entity;

        Entity NewEntity();

        void DrawSprite(Entity entity);
        void DrawTileMap(Entity entity);
        void DrawModel(Entity entity, const Ref<GLShaderProgram>& shader);

        void AddBehaviour(Behaviour* behaviour);

        void StartBehaviours();
        void UpdateBehaviours();

    private:
        entt::registry _registry;
        
        std::vector<Behaviour*> _behaviours;
    };
}

