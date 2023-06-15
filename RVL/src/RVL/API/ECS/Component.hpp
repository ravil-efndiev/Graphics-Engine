#pragma once

namespace Rvl
{   
    class Entity;

    class Component
    {
    public:
        Component() = default;
        Component(Entity* self);
        virtual ~Component();

        virtual void Update() = 0;


    protected:
        Entity* _self;
    };
}

