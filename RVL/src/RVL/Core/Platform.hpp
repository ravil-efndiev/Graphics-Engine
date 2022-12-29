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
 * \brief For use by user functions and specified semantic variables
*/
#pragma region primitive_types

typedef signed long  rvli64;
typedef signed int   rvli32;
typedef signed short rvli16;
typedef signed char  rvli8;

typedef unsigned long  rvlui64;
typedef unsigned int   rvlui32;
typedef unsigned short rvlui16;
typedef unsigned char  rvlui8;

typedef rvlui8  rvlubyte;
typedef rvli8   rvlbyte;

typedef float  rvl_float;
typedef double rvl_double;

#pragma endregion

/// (RVL_DEBUG or RVL_RELEASE)
/// ===== Current engine mode =====
#define RVL_DEBUG  
///================================

#ifdef RVL_DEBUG

#define RVL_DEBUG_BREAK asm volatile ("int3")

#define RVL_LOG(text) std::cout << text << std::endl
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

/**
 * \brief For use in specific cases by RVL API
*/
#pragma region specific_types
typedef rvlui16  rvlStatus_t;
typedef rvli64   rvlKeycode_t;
typedef rvlui64  rvlSizei_t;
#pragma endregion

namespace rvl
{
    /**
     * structure to process errors that can be caused by user
     * example: usage of incorrect value in api function
     * it has text variable and Print function to print error
     * 
     * also it provides static function to print error text given
    */
    struct Error
    {   
        std::string _text;
        rvlStatus_t _status;
        Error(const std::string& text, rvlStatus_t status) : _text(text), _status(status) {}

        void Print()
        {
            std::cerr << "RUNTIME_ERROR => " << _text << std::endl;
        }

        static void PrintErrorS(const std::string& text)
        {
            std::cerr << "RUNTIME_ERROR => " << text << std::endl;
        }
    };

    /**
     * Keyboard codes for user input
    */
    enum class Keys : rvlKeycode_t
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

    // rvlKeycode_t is actual number type that should be passed in engine functions
    // rvlKeycode_e is enum type to be passed in api functions and used by users
    //              is inherited from rvlKeycode_t
    typedef Keys rvlKeycode_e;

}

#endif
