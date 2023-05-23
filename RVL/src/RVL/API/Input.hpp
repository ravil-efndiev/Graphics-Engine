#ifndef RVL_INPUT_HPP
#define RVL_INPUT_HPP

#include <Core/Core.hpp>
#include <API/Math/Math.hpp>

namespace rvl
{    

    class Input
    {
    public:
        static bool IsKeyPressed(keycode_e keycode);

        static bool IsKeyPressedOnce(keycode_e keycode);

        /**
         * @brief get all axis-related key inputs, gets one-frame key press
         * 
         * @returns -1.f or 1.f depending on what input is got
         * 
         * @ingroup input
        */
        static float GetAxis(Axis axis);

        static glm::vec2 GetCursorPosition();
        static glm::vec2 GetCursorPositionRelative(const glm::vec2& mainViewport, const glm::vec2& currentViewport);
        static glm::vec2 GetCursorPositionRaw();

    };
}

#endif
