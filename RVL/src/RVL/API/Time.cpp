#include "Time.hpp"

#include <glfw/glfw3.h>
#include <Core/Core.hpp>

namespace rvl
{
    TimeStep Time::_time;
    TimeStep Time::_deltaTime;
    TimeStep Time::_lastTime = 0.f;

    void Time::Update()
    {
        _time = glfwGetTime();
        _deltaTime = _time - _lastTime;
        _lastTime = _time;
    
        //RVL_LOG("delta time: " << _deltaTime);
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
}
