#ifndef RVL_COMPONENT_HPP
#define RVL_COMPONENT_HPP

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

#endif
