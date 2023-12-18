#pragma once

#include <API/Time.hpp>
#include <Core/Core.hpp>
#include <Entity.hpp>

namespace Rvl
{
    enum class MoveState4
    {
        StandUp, MoveUp,
        StandDown, MoveDown,
        StandRight, MoveRight,
        StandLeft, MoveLeft,
    };

    class Movement2D
    {
    public:
        Movement2D() = default;
        Movement2D(const Movement2D&) = default;
        Movement2D(float maxVelocity, float acceleration, float deceleration);
        ~Movement2D();

        void Update();
        void Move(float x, float y);

        void StopVelocity();
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
        MoveState4 _lastState;
        MoveState4 _currentState = MoveState4::StandDown;

        float _maxVelocity;

        glm::vec2 _velocity;
        float _acceleration;
        float _deceleration;
    };
}

