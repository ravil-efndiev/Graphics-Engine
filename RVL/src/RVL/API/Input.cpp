#include "Input.hpp"
#include <Core/EventListener.hpp>

namespace rvl
{
    bool Input::IsKeyPressed(rvlKeycode_e keycode)
    {
        rvlKeycode_t realKeycode = static_cast<rvlKeycode_t>(keycode);

        if (realKeycode >= MOUSE_BUTTONS_OFFSET)
            throw rvl::Error("passed mouse button code in KeyPressed function", RVL_RUNTIME_ERROR);
        return EventListener::GetKey(realKeycode);
    }

    bool Input::IsKeyPressedOnce(rvlKeycode_e keycode)
    {
        rvlKeycode_t realKeycode = static_cast<rvlKeycode_t>(keycode);

        if (realKeycode >= MOUSE_BUTTONS_OFFSET)
            throw rvl::Error("passed mouse button code in KeyPressed function", RVL_RUNTIME_ERROR);
        return EventListener::GetKeyWithFrame(realKeycode);
    }
}
