#ifndef RVL_MOVEMENTCOMPONENT_HPP
#define RVL_MOVEMENTCOMPONENT_HPP

#include <API/Objects/Entity.hpp>
#include <API/Time.hpp>

namespace rvl
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
        static Ref<MovementComponent> Create(Transform* targetTransform, float maxVelocity, float acceleration, float deceleration);

        MovementComponent(Transform* targetTransform, float maxVelocity, float acceleration, float deceleration);
        ~MovementComponent();

        // User side-only called methods
        void Start() override;
        void Update() override;

        // User / engine side call
        // by defalt is called whenever  component gets attached to an entity
        void OnAttach() override;

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
        Transform* _targetTransform;

        MoveState4 _lastState;
        MoveState4 _currentState = MoveState4::StandDown;

        float _maxVelocity;

        glm::vec2 _velocity;
        float _acceleration;
        float _deceleration;

    };
}

#endif
