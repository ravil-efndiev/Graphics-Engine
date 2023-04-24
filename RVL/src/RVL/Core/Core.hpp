#ifndef RVL_PLATFORM_HPP
#define RVL_PLATFORM_HPP

///////////////////////////////////////////
/////  current engine configuration  //////
///////////////////////////////////////////
#define RVL_DEBUG  

#include "Macros.hpp"
#include "Error.hpp"
#include "Keys.hpp"
#include "Pointers.hpp"

/**
 * For use by user functions and specified semantic variables
*/
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

    typedef uint8  ubyte;
    typedef int8   byte;

    typedef float  float32;
    typedef double float64;
}

#endif
