#include "Time.hpp"

#include <glfw/glfw3.h>
#include <Core/Core.hpp>

namespace rvl
{
    float Time::_time;
    float Time::_deltaTime;
    float Time::_lastTime = 0.f;

    void Time::Update()
    {
        _time = glfwGetTime();
        _deltaTime = _time - _lastTime;
        _lastTime = _time;
        
        RVL_LOG("delta time: " << _deltaTime);
    }

    float Time::Now()
    {
        return _time;
    }

    float Time::DeltaTime()
    {
        return _deltaTime;
    }

    float Time::LastTime()
    {
        return _lastTime;
    }
}
