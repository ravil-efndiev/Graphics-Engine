#ifndef RVL_MACROS_HPP
#define RVL_MACROS_HPP

#include <Rvlpch.hpp>

#define RVL_ENTRY_FUNCTION __attribute__((weak))

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

#endif
