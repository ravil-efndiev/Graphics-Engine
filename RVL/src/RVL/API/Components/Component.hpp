#ifndef RVL_COMPONENT_HPP
#define RVL_COMPONENT_HPP

namespace rvl
{
    class Component
    {
    public:
        Component();
        virtual ~Component();

        // User side-only called methods
        virtual void Start() = 0;
        virtual void Update() = 0;

        // User / engine side call
        // by defalt is called whenever  component gets attached to an entity
        virtual void OnAttach() = 0;    
        
    private:

    };
}

#endif
