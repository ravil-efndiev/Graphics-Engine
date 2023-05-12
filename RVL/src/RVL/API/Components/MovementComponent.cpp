#include "MovementComponent.hpp"

namespace rvl
{
    Ref<MovementComponent> MovementComponent::Create(Transform* targetTransform, float maxVelocity, float acceleration, float deceleration)
    {
        return CreateRef<MovementComponent>(targetTransform, maxVelocity, acceleration, deceleration);
    }


    MovementComponent::MovementComponent(Transform* targetTransform, float maxVelocity, float acceleration, float deceleration)
        : _targetTransform(targetTransform), _maxVelocity(maxVelocity), 
        _acceleration(acceleration), _deceleration(deceleration) {}

    MovementComponent::~MovementComponent() {}
    
    void MovementComponent::Start()
    {
    }
    
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

        _targetTransform->Position.x += _velocity.x * Time::DeltaTime();
        _targetTransform->Position.y += _velocity.y * Time::DeltaTime();
    }
    
    void MovementComponent::OnAttach()
    {
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
}
