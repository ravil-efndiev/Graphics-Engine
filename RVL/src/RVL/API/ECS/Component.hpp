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

    protected:
        Entity* _self = nullptr;
    };
}

