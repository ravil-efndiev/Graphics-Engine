#pragma once

namespace Rvl
{
    class Component
    {
    public:
        Component();
        virtual ~Component();

        virtual void Update() = 0;
    };
}

