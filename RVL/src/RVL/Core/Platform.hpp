#ifndef RVL_PLATFORM_HPP
#define RVL_PLATFORM_HPP

#include <Rvlpch.hpp>

/**
 * 
 * 
 *          BASIC DESCRIPTION
 * 
 * 
*/

#define RVL_ENTRY_FUNCTION __attribute__((weak))

// statuses
#define RVL_SUCCESS         0
#define RVL_INTERNAL_ERROR  1
#define RVL_RUNTIME_ERROR   2

/**
 * For use by user functions and specified semantic variables
*/
#pragma region primitive_types
namespace rvl
{
    typedef signed long  int64;
    typedef signed int   int32;
    typedef signed short int16;
    typedef signed char  int8;

    typedef unsigned long  uint64;
    typedef unsigned int   uint32;
    typedef unsigned short uint16;
    typedef unsigned char  uint8;

    typedef uint8  unsignedByte;
    typedef int8   byte;

    typedef float  float32;
    typedef double double64;
}

#pragma endregion

///////////////////////////////////////////
/////  current engine configuration  //////
///////////////////////////////////////////
#define RVL_DEBUG  

#ifdef RVL_DEBUG

#define RVL_DEBUG_BREAK asm volatile ("int3")

#define RVL_LOG(text) std::cout << "LOG => " << text << std::endl
#define RVL_LOG_ERROR(err) std::cerr << "DEBUG_ERROR => " << err << std::endl

/**
 * used only for error checking in debug mode for errors that can be caused by engine itself
 * \note for errors that caused by user or any other errors that can be caused in release mode use rvl::Error struct
*/
#define RVL_ASSERT(cond, text) if(!cond) { \
                               RVL_LOG_ERROR(text); \
                               RVL_DEBUG_BREAK; } 
#else

#define RVL_DEBUG_BREAK

#define RVL_LOG(text)
#define RVL_LOG_ERROR(err)

#define RVL_ASSERT(cond, text) if (!cond) throw rvl::Error("INTERNAL ENGINE ERROR", RVL_INTERNAL_ERROR);

#endif


namespace rvl
{
    typedef uint16  status_t;

    /**
     * structure to process errors that can be caused by user
     * example: usage of incorrect value in api function
     * it has text variable and Print function to print error
     * 
     * also it provides static function to print error text given
    */
    struct Error
    {   
        std::string Text;
        status_t Status;
        Error(const std::string& text, status_t status) : Text(text), Status(status) {}

        void Print()
        {
            std::cerr << "RUNTIME_ERROR => " << Text << std::endl;
        }

        static void PrintErrorS(const std::string& text)
        {
            std::cerr << "RUNTIME_ERROR => " << text << std::endl;
        }
    };


    // specific type for key and mouse codes
    // should be used in lower level engine functions
    // in api functions keycode_e must be used
    typedef int64   keycode_t;
    typedef uint64  sizei_t;
    

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
