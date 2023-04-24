#ifndef RVL_KEYS_HPP
#define RVL_KEYS_HPP

namespace rvl
{

    // specific type for key and mouse codes
    // should be used in lower level engine functions
    // in api functions keycode_e must be used
    typedef long   keycode_t;

    /**
     * Keyboard codes for user input
    */
    enum class Keys : keycode_t
    {
        RVL_KEY_SPACE             = 32,
        RVL_KEY_APOSTROPHE        = 39,  /* ' */
        RVL_KEY_COMMA             = 44,  /* , */
        RVL_KEY_MINUS             = 45,  /* - */
        RVL_KEY_PERIOD            = 46,  /* . */
        RVL_KEY_SLASH             = 47,  /* / */
        RVL_KEY_0                 = 48,
        RVL_KEY_1                 = 49,
        RVL_KEY_2                 = 50,
        RVL_KEY_3                 = 51,
        RVL_KEY_4                 = 52,
        RVL_KEY_5                 = 53,
        RVL_KEY_6                 = 54,
        RVL_KEY_7                 = 55,
        RVL_KEY_8                 = 56,
        RVL_KEY_9                 = 57,
        RVL_KEY_SEMICOLON         = 59,  /* ; */
        RVL_KEY_EQUAL             = 61,  /* = */
        RVL_KEY_A                 = 65,
        RVL_KEY_B                 = 66,
        RVL_KEY_C                 = 67,
        RVL_KEY_D                 = 68,
        RVL_KEY_E                 = 69,
        RVL_KEY_F                 = 70,
        RVL_KEY_G                 = 71,
        RVL_KEY_H                 = 72,
        RVL_KEY_I                 = 73,
        RVL_KEY_J                 = 74,
        RVL_KEY_K                 = 75,
        RVL_KEY_L                 = 76,
        RVL_KEY_M                 = 77,
        RVL_KEY_N                 = 78,
        RVL_KEY_O                 = 79,
        RVL_KEY_P                 = 80,
        RVL_KEY_Q                 = 81,
        RVL_KEY_R                 = 82,
        RVL_KEY_S                 = 83,
        RVL_KEY_T                 = 84,
        RVL_KEY_U                 = 85,
        RVL_KEY_V                 = 86,
        RVL_KEY_W                 = 87,
        RVL_KEY_X                 = 88,
        RVL_KEY_Y                 = 89,
        RVL_KEY_Z                 = 90,
        RVL_KEY_LEFT_BRACKET      = 91,  /* [ */
        RVL_KEY_BACKSLASH         = 92,  /* \ */
        RVL_KEY_RIGHT_BRACKET     = 93,  /* ] */
        RVL_KEY_GRAVE_ACCENT      = 96,  /* ` */
        RVL_KEY_WORLD_1           = 161, /* non-US #1 */
        RVL_KEY_WORLD_2           = 162, /* non-US #2 */
    };

    // keycode_e is enum type to be passed in api functions and used by users
    // notice: if you want to get only raw key code use keycode_t
    // also its easy to cast keycode_e to keycode_t because Keys enum has type keycode_t
    // api should ALWAYS take this type (keycode_e)
    // while lower level engine functions should take keycode_t
    typedef Keys keycode_e;
}

#endif
