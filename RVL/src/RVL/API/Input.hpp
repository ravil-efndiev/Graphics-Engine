#ifndef RVL_INPUT_HPP
#define RVL_INPUT_HPP

#include <Core/Platform.hpp>

namespace rvl
{    

    class Input
    {
    public:
        /**
         * @brief Checks if key is pressed 
         * 
         * @returns Function returns true all the time while key is pressed 
         *
         * @note If you need to check key press once use "IsKeyPressedDown" function
         * @ingroup input
        */
        static bool IsKeyPressed(rvlKeycode_t keycode);

    private:

    };
}

#endif
