#ifndef RVL_MOVEMENTCOMPONENT_HPP
#define RVL_MOVEMENTCOMPONENT_HPP

#include "Component.hpp"

namespace rvl
{
    class MovementComponent : public Component
    {
    public:
        MovementComponent();
        ~MovementComponent();

        // User side-only called methods
        void Start() override;
        void Update() override;

        // User / engine side call
        // by defalt is called whenever  component gets attached to an entity
        void OnAttach() override;

    private:

    };
}

#endif
