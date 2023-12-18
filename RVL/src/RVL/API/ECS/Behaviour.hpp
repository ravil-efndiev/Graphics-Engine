#pragma once

#include "General/Transform.hpp"
#include <Events/Events.hpp>

#define RVL_BEHAVIOUR(Type) Type(Entity& self) : Behaviour(self) {} \
                           ~Type() {}

#define RVL_ADD_BEHAVIOUR(scene, entity, type) scene.AddBehaviour(&entity.AddComponent<type>(entity));

namespace Rvl
{
    class Entity;
    class Behaviour
    {
    public:
        Behaviour(Entity& self);
        virtual ~Behaviour();

        virtual void Start() {}
        virtual void Update() {}
        virtual void Tick() {}

        virtual void OnEvent(Event* event) {}

    protected:
        Entity& _self;
        Transform& _transform;
    };
}

