#include "Input.hpp"
#include <Events/EventListener.hpp>

#include <Rendering/Renderer/Renderer.hpp>

namespace Rvl
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

    bool Input::IsMouseButtonPressed(mouseButton_e button)
    {
        keycode_t realCode = static_cast<keycode_t>(button);

        if (realCode < MOUSE_BUTTONS_OFFSET)
            throw Error("passed key code in mouse input function", RVL_RUNTIME_ERROR);
            
        return EventListener::GetKey(realCode);
    }

    bool Input::IsMouseButtonPressedOnce(mouseButton_e button)
    {
        keycode_t realCode = static_cast<keycode_t>(button);

        if (realCode < MOUSE_BUTTONS_OFFSET)
            throw Error("passed key code in mouse input function", RVL_RUNTIME_ERROR);

        return EventListener::GetKeyWithFrame(realCode);
    }

    float Input::GetAxis(Axis axis)
    {
        if (axis == Axis::Horizontal)
        {
            if (IsKeyPressed(Keys::Key_D) || IsKeyPressed(Keys::Key_Right))
                return 1.f;

            if (IsKeyPressed(Keys::Key_A) || IsKeyPressed(Keys::Key_Left))
                return -1.f;
            
            return 0.f;
        }
        else if (axis == Axis::Vertical)
        {
            if (IsKeyPressed(Keys::Key_W) || IsKeyPressed(Keys::Key_Up))
                return 1.f;

            if (IsKeyPressed(Keys::Key_S) || IsKeyPressed(Keys::Key_Down))
                return -1.f;

            return 0.f;
        }
        else throw Error("Invalid axis parameter to GetAxis method", RVL_RUNTIME_ERROR);
    }

    glm::vec2 Input::GetCursorPosition()
    {
        return Renderer::ConvertToWorldCoords(EventListener::GetCursorPosX(), EventListener::GetCursorPosY());
    }

    glm::vec2 Input::GetCursorPositionRelative(const glm::vec2& mainViewport, const glm::vec2& currentViewport)
    {
        glm::vec2 pos = Renderer::ConvertToWorldCoords(
            EventListener::GetCursorPosX(),
            EventListener::GetCursorPosY(),
            currentViewport
        );
        return pos;
    }

    glm::vec2 Input::GetCursorPositionRaw()
    {
        return glm::vec2(EventListener::GetCursorPosX(), EventListener::GetCursorPosY());
    }
    
    glm::vec2 Input::GetCursorDelta()
    {
        return {-EventListener::GetCursorDeltaX(), -EventListener::GetCursorDeltaY()};
    }
}
