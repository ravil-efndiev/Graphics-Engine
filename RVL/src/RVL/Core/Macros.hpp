#pragma once

#include <Rvlpch.hpp>

#define RVL_ENTRY_FUNCTION __attribute__((weak))

#define RVL_LOG_COLOR_NONE   "\033[0m"

#define RVL_LOG_COLOR_RED    "\033[91m"
#define RVL_LOG_COLOR_GREEN  "\033[92m"
#define RVL_LOG_COLOR_YELLOW "\033[93m"
#define RVL_LOG_COLOR_BLUE   "\033[94m"

#define BIT(n) 1 << n

#ifdef RVL_DEBUG

    #define RVL_DEBUG_BREAK asm volatile ("int3")

    #define RVL_LOG(text) std::cout << RVL_LOG_COLOR_NONE << "LOG => " << text << RVL_LOG_COLOR_NONE << std::endl
    #define RVL_WARN(text) std::cout << RVL_LOG_COLOR_YELLOW << "WARNING => " << text << RVL_LOG_COLOR_NONE << std::endl
    #define RVL_LOG_ERROR(err) std::cerr << RVL_LOG_COLOR_RED << "DEBUG_ERROR => " << err << RVL_LOG_COLOR_NONE << std::endl

    #define RVL_LOG_COLORED(text, color) std::cout << color << "LOG => " << text << RVL_LOG_COLOR_NONE << std::endl
    
    /**
     * used only for error checking in debug mode for errors that can be caused by engine itself
     * \note for errors that caused by user or any other errors that can be caused in release mode use rvl::Error struct
    */
    #define RVL_ASSERT(cond, text) if(!cond) { \
                                RVL_LOG_ERROR(text); \
                                RVL_DEBUG_BREAK; } 
#else

    #define RVL_DEBUG_BREAK

    // TODO: add release functionality to macros below
    #define RVL_LOG(text)
    #define RVL_LOG_ERROR(err)

    #define RVL_ASSERT(cond, text) if (!cond) throw rvl::Error("INTERNAL ENGINE ERROR", RVL_INTERNAL_ERROR);

#endif

