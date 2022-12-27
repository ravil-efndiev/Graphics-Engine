#include "Input.hpp"
#include <Core/EventListener.hpp>

namespace rvl
{
    bool Input::IsKeyPressed(rvlKeycode_t keycode)
    {
        if (keycode >= MOUSE_BUTTONS_OFFSET)
            throw rvl::Error("passed mouse button code in KeyPressed function", RVL_RUNTIME_ERROR);
        return EventListener::GetKey(keycode);
    }
    bool Input::IsKeyPressedOnce(rvlKeycode_t keycode)
    {
        if (keycode >= MOUSE_BUTTONS_OFFSET)
            throw rvl::Error("passed mouse button code in KeyPressed function", RVL_RUNTIME_ERROR);
        return EventListener::GetKeyWithFrame(keycode);
    }
}
