#pragma once

#include "Scene.hpp"

namespace Rvl
{
    class Entity
    {
    public:
        Entity() = default;
        Entity(Scene* scene, entt::entity id);

        template <class T, class... Args>
        T& AddComponent(Args&&... args)
        {
            RVL_ASSERT(!HasComponent<T>(), "Entity already has this component");
            return _scene->_registry.emplace<T>(_id, std::forward<Args>(args)...);
        }

        template <class T>
        T& GetComponent()
        {
            RVL_ASSERT(HasComponent<T>(), "Entity doesn't have the component");
            return _scene->_registry.get<T>(_id);
        }

        template <class T>
        bool HasComponent()
        {
            return _scene->_registry.any_of<T>(_id);
        }

    private:
        entt::entity _id;
        Scene* _scene;
    };
}

