#pragma once

#include "TransformComponent.hpp"

#define RVL_BEHAVIOUR(Type) Type(Entity& self) : Behaviour(self) {} \
                           ~Type() {}

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

    protected:
        Entity& _self;
        TransformComponent& _transform;
    };
}

