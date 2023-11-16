#pragma once
#include <RVL.hpp>

using namespace Rvl;

class TestScript : public Behaviour
{
public:
    RVL_BEHAVIOUR(TestScript)

    void Start() override
    {
    }

    void Update() override
    {
        /*if (Input::IsMouseButtonPressed(Mouse::Left))
            _transform.Position->x += 10 * Time::DeltaTime();*/
    }

    void OnEvent(Event* event) override
    {
        //if (event->GetType() == EventType::MOUSE_BUTTON_PRESSED)
        //    _transform.Rotation->y = 20;
    }
};
