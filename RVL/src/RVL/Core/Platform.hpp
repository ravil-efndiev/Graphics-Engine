#ifndef RVL_PLATFORM_HPP
#define RVL_PLATFORM_HPP

/**
 * 
 * 
 *          BASIC DESCRIPTION
 * 
 * 
*/

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

#define RVL_ASSERT(cond, text) if(!cond) { \
                               RVL_LOG_ERROR(text); \
                               RVL_DEBUG_BREAK; } 
#else

#define RVL_DEBUG_BREAK

#define RVL_LOG(text)
#define RVL_LOG_ERROR(err)

#define RVL_ASSERT(cond, text) ;

#endif

/**
 * \brief For use in specific cases by RVL API
*/
#pragma region specific_types
typedef rvlui16  rvlStatus_t;
typedef rvli32   rvlKeycode_t;
typedef rvlui64  rvlSizei_t;
#pragma endregion

/**
 * Keyboard and mouse codes
*/
/* Printable keys */
#define RVL_KEY_SPACE              32
#define RVL_KEY_APOSTROPHE         39  /* ' */
#define RVL_KEY_COMMA              44  /* , */
#define RVL_KEY_MINUS              45  /* - */
#define RVL_KEY_PERIOD             46  /* . */
#define RVL_KEY_SLASH              47  /* / */
#define RVL_KEY_0                  48
#define RVL_KEY_1                  49
#define RVL_KEY_2                  50
#define RVL_KEY_3                  51
#define RVL_KEY_4                  52
#define RVL_KEY_5                  53
#define RVL_KEY_6                  54
#define RVL_KEY_7                  55
#define RVL_KEY_8                  56
#define RVL_KEY_9                  57
#define RVL_KEY_SEMICOLON          59  /* ; */
#define RVL_KEY_EQUAL              61  /* = */
#define RVL_KEY_A                  65
#define RVL_KEY_B                  66
#define RVL_KEY_C                  67
#define RVL_KEY_D                  68
#define RVL_KEY_E                  69
#define RVL_KEY_F                  70
#define RVL_KEY_G                  71
#define RVL_KEY_H                  72
#define RVL_KEY_I                  73
#define RVL_KEY_J                  74
#define RVL_KEY_K                  75
#define RVL_KEY_L                  76
#define RVL_KEY_M                  77
#define RVL_KEY_N                  78
#define RVL_KEY_O                  79
#define RVL_KEY_P                  80
#define RVL_KEY_Q                  81
#define RVL_KEY_R                  82
#define RVL_KEY_S                  83
#define RVL_KEY_T                  84
#define RVL_KEY_U                  85
#define RVL_KEY_V                  86
#define RVL_KEY_W                  87
#define RVL_KEY_X                  88
#define RVL_KEY_Y                  89
#define RVL_KEY_Z                  90
#define RVL_KEY_LEFT_BRACKET       91  /* [ */
#define RVL_KEY_BACKSLASH          92  /* \ */
#define RVL_KEY_RIGHT_BRACKET      93  /* ] */
#define RVL_KEY_GRAVE_ACCENT       96  /* ` */
#define RVL_KEY_WORLD_1            161 /* non-US #1 */
#define RVL_KEY_WORLD_2            162 /* non-US #2 */

#endif
