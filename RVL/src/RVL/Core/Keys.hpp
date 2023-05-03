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
        RVL_KEY_ESCAPE            = 256,
        RVL_KEY_ENTER             = 257,
        RVL_KEY_TAB               = 258,
        RVL_KEY_BACKSPACE         = 259,
        RVL_KEY_INSERT            = 260,
        RVL_KEY_DELETE            = 261,
        RVL_KEY_RIGHT             = 262,
        RVL_KEY_LEFT              = 263,
        RVL_KEY_DOWN              = 264,
        RVL_KEY_UP                = 265,
        RVL_KEY_PAGE_UP           = 266,
        RVL_KEY_PAGE_DOWN         = 267,
        RVL_KEY_HOME              = 268,
        RVL_KEY_END               = 269,
        RVL_KEY_CAPS_LOCK         = 280,
        RVL_KEY_SCROLL_LOCK       = 281,
        RVL_KEY_NUM_LOCK          = 282,
        RVL_KEY_PRINT_SCREEN      = 283,
        RVL_KEY_PAUSE             = 284,
        RVL_KEY_F1                = 290,
        RVL_KEY_F2                = 291,
        RVL_KEY_F3                = 292,
        RVL_KEY_F4                = 293,
        RVL_KEY_F5                = 294,
        RVL_KEY_F6                = 295,
        RVL_KEY_F7                = 296,
        RVL_KEY_F8                = 297,
        RVL_KEY_F9                = 298,
        RVL_KEY_F10               = 299,
        RVL_KEY_F11               = 300,
        RVL_KEY_F12               = 301,
        RVL_KEY_F13               = 302,
        RVL_KEY_F14               = 303,
        RVL_KEY_F15               = 304,
        RVL_KEY_F16               = 305,
        RVL_KEY_F17               = 306,
        RVL_KEY_F18               = 307,
        RVL_KEY_F19               = 308,
        RVL_KEY_F20               = 309,
        RVL_KEY_F21               = 310,
        RVL_KEY_F22               = 311,
        RVL_KEY_F23               = 312,
        RVL_KEY_F24               = 313,
        RVL_KEY_F25               = 314,
        RVL_KEY_KP_0              = 320,
        RVL_KEY_KP_1              = 321,
        RVL_KEY_KP_2              = 322,
        RVL_KEY_KP_3              = 323,
        RVL_KEY_KP_4              = 324,
        RVL_KEY_KP_5              = 325,
        RVL_KEY_KP_6              = 326,
        RVL_KEY_KP_7              = 327,
        RVL_KEY_KP_8              = 328,
        RVL_KEY_KP_9              = 329,
        RVL_KEY_KP_DECIMAL        = 330,
        RVL_KEY_KP_DIVIDE         = 331,
        RVL_KEY_KP_MULTIPLY       = 332,
        RVL_KEY_KP_MINUS          = 333,
        RVL_KEY_KP_PLUS           = 334,
        RVL_KEY_KP_ENTER          = 335,
        RVL_KEY_KP_EQUAL          = 336,
        RVL_KEY_LEFT_SHIFT        = 340,
        RVL_KEY_LEFT_CONTROL      = 341,
        RVL_KEY_LEFT_ALT          = 342,
        RVL_KEY_LEFT_SUPER        = 343,
        RVL_KEY_RIGHT_SHIFT       = 344,
        RVL_KEY_RIGHT_CONTROL     = 345,
        RVL_KEY_RIGHT_ALT         = 346,
        RVL_KEY_RIGHT_SUPER       = 347,
        RVL_KEY_MENU              = 348,
    };

    // keycode_e is enum type to be passed in api functions and used by users
    // notice: if you want to get only raw key code use keycode_t
    // also its easy to cast keycode_e to keycode_t because Keys enum has type keycode_t
    // api should ALWAYS take this type (keycode_e)
    // while lower level engine functions should take keycode_t
    typedef Keys keycode_e;
}

#endif
