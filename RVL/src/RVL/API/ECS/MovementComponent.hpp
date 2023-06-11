#ifndef RVL_MOVEMENTCOMPONENT_HPP
#define RVL_MOVEMENTCOMPONENT_HPP

#include <API/Time.hpp>
#include <Core/Core.hpp>
#include "Entity.hpp"
#include "Component.hpp"
#include "TransformComponent.hpp"
#include <Rendering/Renderer/Transform.hpp>

namespace Rvl
{
    enum class MoveState4
    {
        StandUp, MoveUp,
        StandDown, MoveDown,
        StandRight, MoveRight,
        StandLeft, MoveLeft,
    };

    class MovementComponent : public Component
    {
    public:
        MovementComponent() = default;
        MovementComponent(const MovementComponent&) = default;
        MovementComponent(Entity* target, float maxVelocity, float acceleration, float deceleration);
        ~MovementComponent();

        void Update() override;

        void StopVelocity();

        void Move(float x, float y);

        glm::vec2 GetVelocity() const;

        float GetMaxVelocity() const;
        float GetAcceleration() const;
        float GetDeceleration() const;

        void SetAcceleration(float acceleration);
        void SetDeceleration(float deceleration);
        void SetMaxVelocity(float maxVelocity);

        // x axis movement is prioritized
        MoveState4 GetMoveState4() const;

    private:
        Entity* _target;

        MoveState4 _lastState;
        MoveState4 _currentState = MoveState4::StandDown;

        float _maxVelocity;

        glm::vec2 _velocity;
        float _acceleration;
        float _deceleration;

    };
}

#endif
