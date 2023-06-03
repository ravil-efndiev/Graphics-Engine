#ifndef RVL_ENTITY_HPP
#define RVL_ENTITY_HPP

#include <Rendering/Renderer/Transform.hpp>
#include <API/Components/Component.hpp>
#include <API/Property.hpp>

#include <Core/Utils/Types.hpp>

namespace Rvl
{

    class Entity
    {
    public:
        Entity();
        Entity(const Transform& tf);
        virtual ~Entity();

        Property<Transform> transform = {&_transform};

        template <class CmpT>
        Ref<Component> GetComponent();

        void AddChild(const Ref<Entity>& entity);
        void AddComponent(const Ref<Component>& component);

    protected:

        void UpdateChildren();

        Transform _transform;

        std::vector<Ref<Entity>> _children;
        std::vector<Ref<Component>> _components;

        bool _hasParent = false;
        bool _hasChildren = false;

        glm::vec3 _realPosition;
        float _realRotationZ;
    };

    template<class CmpT>
    Ref<Component> Entity::GetComponent()
    {
        if (_components.size() <= 0)
            return nullptr;

        for (auto& cmp : _components)
        {
            if (Utils::InstanceOf<CmpT>(cmp.get()))
            {
                return cmp;
            }
        }

        return nullptr;
    }
}

#endif
