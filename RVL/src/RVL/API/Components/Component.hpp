#ifndef RVL_COMPONENT_HPP
#define RVL_COMPONENT_HPP

namespace rvl
{
    class Component
    {
    public:
        Component();
        virtual ~Component();

        virtual void Attach() = 0;    
        virtual void Update() = 0;

    private:

    };
}

#endif
