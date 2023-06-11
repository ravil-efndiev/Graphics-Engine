#ifndef RVL_SCENE_HPP
#define RVL_SCENE_HPP

#include <entt/entt.hpp>
#include <Core/Core.hpp>

namespace Rvl
{
    class Entity;

    class Scene
    {
    public:
        Scene();
        ~Scene();

        friend class Entity;

        Entity NewEntity();

        void DrawSprite(Entity entity);
        void DrawTileMap(Entity entity);

    private:
        entt::registry _registry;
    };
}

#endif
