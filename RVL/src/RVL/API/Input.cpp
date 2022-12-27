#include "Input.hpp"
#include <Core/EventListener.hpp>

namespace rvl
{
    bool Input::IsKeyPressed(rvlKeycode_t keycode)
    {
        return EventListener::GetKey(keycode);
    }
} 
