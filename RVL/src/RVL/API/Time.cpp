#include "Time.hpp"

#include <glfw/glfw3.h>
#include <Core/Core.hpp>

namespace Rvl
{
    TimeStep Time::_time;
    TimeStep Time::_deltaTime;
    TimeStep Time::_lastTime = 0.f;

    void Time::Update()
    {
        _time = glfwGetTime();
        _deltaTime = _time - _lastTime;
        _lastTime = _time;
    }

    TimeStep Time::Current()
    {
        return _time;
    }

    TimeStep Time::DeltaTime()
    {
        return _deltaTime;
    }

    TimeStep Time::LastTime()
    {
        return _lastTime;
    }
    
    TimeStep Time::FixedDeltaTime()
    {
        return 1.f / 60.f;
    }
}
