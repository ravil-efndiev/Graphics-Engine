#include "MovementComponent.hpp"

namespace Rvl
{
    MovementComponent::MovementComponent(Entity* target, float maxVelocity, float acceleration, float deceleration)
        : _target(target), _maxVelocity(maxVelocity), 
        _acceleration(acceleration), _deceleration(deceleration) {}

    MovementComponent::~MovementComponent() {}
    
    void MovementComponent::Update()
    {
        if (_velocity.x > 0.f)
        {
            if (_velocity.x > _maxVelocity)
                _velocity.x = _maxVelocity;

            _velocity.x -= _deceleration * Time::DeltaTime();
            if (_velocity.x < 0.f)
                _velocity.x = 0.f;
        }

        else if (_velocity.x < 0.f)
        {
            if (_velocity.x < -_maxVelocity)
                _velocity.x = -_maxVelocity;

            _velocity.x += _deceleration * Time::DeltaTime();
            if (_velocity.x > 0.f)
                _velocity.x = 0.f;
        }
        
        if (_velocity.y > 0.f)
        {
            if (_velocity.y > _maxVelocity)
                _velocity.y = _maxVelocity;

            _velocity.y -= _deceleration * Time::DeltaTime();
            if (_velocity.y < 0.f)
                _velocity.y = 0.f;
        }

        else if (_velocity.y < 0.f) 
        {
            if (_velocity.y < -_maxVelocity)
                _velocity.y = -_maxVelocity;

            _velocity.y += _deceleration * Time::DeltaTime();
            if (_velocity.y > 0.f)
                _velocity.y = 0.f;
        }

        _target->GetComponent<TransformComponent>().Position->x += _velocity.x * Time::DeltaTime();
        _target->GetComponent<TransformComponent>().Position->y += _velocity.y * Time::DeltaTime();

        _lastState = _currentState;

        if (_velocity.x > 0.f)
            _currentState = MoveState4::MoveRight;

        else if (_velocity.x < 0.f)
            _currentState = MoveState4::MoveLeft;
        
        else if (_velocity.y > 0.f)
            _currentState = MoveState4::MoveUp;

        else if (_velocity.y < 0.f) 
            _currentState = MoveState4::MoveDown;

        else if (_velocity.x == 0.f && _velocity.y == 0.f)
        {
            switch (_lastState)
            {
                case MoveState4::StandRight:
                case MoveState4::MoveRight:
                    _currentState = MoveState4::StandRight;
                    break;

                case MoveState4::StandLeft:
                case MoveState4::MoveLeft:
                    _currentState = MoveState4::StandLeft;
                    break;

                case MoveState4::StandUp:
                case MoveState4::MoveUp:
                    _currentState = MoveState4::StandUp;
                    break;

                case MoveState4::StandDown:
                case MoveState4::MoveDown:
                    _currentState = MoveState4::StandDown;
                    break;
            }
        }

    }
    
    void MovementComponent::StopVelocity()
    {
        _velocity = {0.f, 0.f};
    }

    void MovementComponent::Move(float x, float y)
    {
        _velocity.x += _acceleration * x * Time::DeltaTime();
        _velocity.y += _acceleration * y * Time::DeltaTime();
    }
    
    glm::vec2 MovementComponent::GetVelocity() const
    {
        return _velocity;
    }

    float MovementComponent::GetMaxVelocity() const
    {
        return _maxVelocity;
    }
    
    float MovementComponent::GetAcceleration() const
    {
        return _acceleration;
    }

    float MovementComponent::GetDeceleration() const
    {
        return _deceleration;
    }
    
    void MovementComponent::SetAcceleration(float acceleration)
    {
        _acceleration = acceleration;
    }
    
    void MovementComponent::SetDeceleration(float deceleration)
    {
        _deceleration = deceleration;
    }
    
    void MovementComponent::SetMaxVelocity(float maxVelocity)
    {
        _maxVelocity = maxVelocity;
    }
    
    MoveState4 MovementComponent::GetMoveState4() const
    {
        return _currentState;
    }
}
