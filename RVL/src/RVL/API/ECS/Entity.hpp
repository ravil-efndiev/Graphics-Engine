#pragma once
#include "Scene.hpp"
#include "General/Transform.hpp"

namespace Rvl
{
    struct EntityData
    {
        std::vector<Entity> Children;
        Transform LastTransformValue;
        std::vector<Transform*> Instances;
        size_t LastTransformsSize = 0;
        bool IsInstance = false;
    };

    class Entity
    {
    public:
        Entity() = default;
        Entity(Scene* scene, entt::entity id);

        template <class T, class... Args>
        T& Add(Args&&... args)
        {
            RVL_ASSERT(!Has<T>(), "Entity already has the component you were trying to add");
            return _scene->_registry.emplace<T>(_id, std::forward<Args>(args)...);
        }

        template <class T>
        T& AddBehaviour()
        {
            RVL_ASSERT(!Has<T>(), "Entity already has the component you were trying to add");
            T& cmp = Add<T>(*this);
            _scene->AddBehaviour(&cmp);
            return cmp;
        }

        template <class T>
        T& Get()
        {
            RVL_ASSERT(Has<T>(), "Entity doesn't have the component you were trying to get");
            return _scene->_registry.get<T>(_id);
        }

        template <class T>
        bool Has()
        {
            return _scene->_registry.any_of<T>(_id);
        }

        template <class T>
        void Remove()
        {
            RVL_ASSERT(Has<T>(), "Entity doesn't have the component you were trying to remove");
            _scene->_registry.remove<T>(_id);
        }

        bool operator==(const Entity& entity) const;

        entt::entity GetId() const;
        uint32 GetIdInt() const;

        void AddChild(Entity child);
        void RemoveChild(Entity child);
        Entity Instantiate();

        EntityData& GetData();

    private:
        entt::entity _id;
        Scene* _scene;
    };
}

