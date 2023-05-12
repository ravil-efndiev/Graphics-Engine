#include "Input.hpp"
#include <Events/EventListener.hpp>

#include <Rendering/Renderer/Renderer.hpp>

namespace rvl
{
    bool Input::IsKeyPressed(keycode_e keycode)
    {
        keycode_t realKeycode = static_cast<keycode_t>(keycode);

        if (realKeycode >= MOUSE_BUTTONS_OFFSET)
            throw Error("passed mouse button code in KeyPressed function", RVL_RUNTIME_ERROR);
        return EventListener::GetKey(realKeycode);
    }

    bool Input::IsKeyPressedOnce(keycode_e keycode)
    {
        keycode_t realKeycode = static_cast<keycode_t>(keycode);

        if (realKeycode >= MOUSE_BUTTONS_OFFSET)
            throw Error("passed mouse button code in KeyPressed function", RVL_RUNTIME_ERROR);
        return EventListener::GetKeyWithFrame(realKeycode);
    }

    float Input::GetAxis(Axis axis)
    {
        if (axis == Axis::Horizontal)
        {
            if (IsKeyPressed(Keys::RVL_KEY_D) || IsKeyPressed(Keys::RVL_KEY_RIGHT))
                return 1.f;

            if (IsKeyPressed(Keys::RVL_KEY_A) || IsKeyPressed(Keys::RVL_KEY_LEFT))
                return -1.f;
            
            return 0.f;
        }
        else if (axis == Axis::Vertical)
        {
            if (IsKeyPressed(Keys::RVL_KEY_W) || IsKeyPressed(Keys::RVL_KEY_UP))
                return 1.f;

            if (IsKeyPressed(Keys::RVL_KEY_S) || IsKeyPressed(Keys::RVL_KEY_DOWN))
                return -1.f;

            return 0.f;
        }
        else throw Error("Invalid axis parameter to GetAxis method", RVL_RUNTIME_ERROR);
    }

    glm::vec2 Input::GetCursorPosition()
    {
        return Renderer::ConvertToWorldCoords(EventListener::GetCursorPosX(), EventListener::GetCursorPosY());
    }
}
