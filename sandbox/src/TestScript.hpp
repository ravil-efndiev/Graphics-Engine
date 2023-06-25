#pragma once
#include <RVL.hpp>

using namespace Rvl;

class TestScript : public Behaviour
{
public:
    RVL_BEHAVIOUR(TestScript)

    void Start() override
    {
        _movement = &_self.AddComponent<MovementComponent>(14.f, 160.f, 120.f);
    }

    void Update() override
    {
        _movement->Move(Input::GetAxis(Axis::Horizontal), Input::GetAxis(Axis::Vertical));
    }

private:
    MovementComponent* _movement;
};

