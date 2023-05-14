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
    enum Keys : keycode_t
    {
        Key_Space             = 32,
        Key_Apostrophe        = 39,  /* ' */
        Key_Comma             = 44,  /* , */
        Key_Minus             = 45,  /* - */
        Key_Period            = 46,  /* . */
        Key_Slash             = 47,  /* / */
        Key_0                 = 48,
        Key_1                 = 49,
        Key_2                 = 50,
        Key_3                 = 51,
        Key_4                 = 52,
        Key_5                 = 53,
        Key_6                 = 54,
        Key_7                 = 55,
        Key_8                 = 56,
        Key_9                 = 57,
        Key_Semicolon         = 59,  /* ; */
        Key_Equal             = 61,  /* = */
        Key_A                 = 65,
        Key_B                 = 66,
        Key_C                 = 67,
        Key_D                 = 68,
        Key_E                 = 69,
        Key_F                 = 70,
        Key_G                 = 71,
        Key_H                 = 72,
        Key_I                 = 73,
        Key_J                 = 74,
        Key_K                 = 75,
        Key_L                 = 76,
        Key_M                 = 77,
        Key_N                 = 78,
        Key_O                 = 79,
        Key_P                 = 80,
        Key_Q                 = 81,
        Key_R                 = 82,
        Key_S                 = 83,
        Key_T                 = 84,
        Key_U                 = 85,
        Key_V                 = 86,
        Key_W                 = 87,
        Key_X                 = 88,
        Key_Y                 = 89,
        Key_Z                 = 90,
        Key_LeftBracket       = 91,  /* [ */
        Key_Backslash         = 92,  /* \ */
        Key_RightBracket      = 93,  /* ] */
        Key_GraveAccent       = 96,  /* ` */
        Key_World_1           = 161, /* non-US #1 */
        Key_World_2           = 162, /* non-US #2 */
        Key_Escape            = 256,
        Key_Enter             = 257,
        Key_Tab               = 258,
        Key_Backspace         = 259,
        Key_Insert            = 260,
        Key_Delete            = 261,
        Key_Right             = 262,
        Key_Left              = 263,
        Key_Down              = 264,
        Key_Up                = 265,
        Key_PageUp            = 266,
        Key_PageDown          = 267,
        Key_Home              = 268,
        Key_End               = 269,
        Key_CapsLock          = 280,
        Key_ScrollLock        = 281,
        Key_NumLock           = 282,
        Key_PrintScreen       = 283,
        Key_Pause             = 284,
        Key_F1                = 290,
        Key_F2                = 291,
        Key_F3                = 292,
        Key_F4                = 293,
        Key_F5                = 294,
        Key_F6                = 295,
        Key_F7                = 296,
        Key_F8                = 297,
        Key_F9                = 298,
        Key_F10               = 299,
        Key_F11               = 300,
        Key_F12               = 301,
        Key_F13               = 302,
        Key_F14               = 303,
        Key_F15               = 304,
        Key_F16               = 305,
        Key_F17               = 306,
        Key_F18               = 307,
        Key_F19               = 308,
        Key_F20               = 309,
        Key_F21               = 310,
        Key_F22               = 311,
        Key_F23               = 312,
        Key_F24               = 313,
        Key_F25               = 314,
        Key_KP_0              = 320,
        Key_KP_1              = 321,
        Key_KP_2              = 322,
        Key_KP_3              = 323,
        Key_KP_4              = 324,
        Key_KP_5              = 325,
        Key_KP_6              = 326,
        Key_KP_7              = 327,
        Key_KP_8              = 328,
        Key_KP_9              = 329,
        Key_KP_Decimal        = 330,
        Key_KP_Divide         = 331,
        Key_KP_Multiply       = 332,
        Key_KP_Minus          = 333,
        Key_KP_Plus           = 334,
        Key_KP_Enter          = 335,
        Key_KP_Equal          = 336,
        Key_LeftShift         = 340,
        Key_LeftControl       = 341,
        Key_LeftAlt           = 342,
        Key_LeftSuper         = 343,
        Key_RightShift        = 344,
        Key_RightControl      = 345,
        Key_RightAlt          = 346,
        Key_RightSuper        = 347,
        Key_Menu              = 348,
    };

    // keycode_e is enum type to be passed in api functions and used by users
    // notice: if you want to get only raw key code use keycode_t
    // also its easy to cast keycode_e to keycode_t because Keys enum has type keycode_t
    // api should ALWAYS take this type (keycode_e)
    // while lower level engine functions should take keycode_t
    typedef Keys keycode_e;
}

#endif
