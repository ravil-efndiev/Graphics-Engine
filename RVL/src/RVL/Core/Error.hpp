#ifndef RVL_ERROR_HPP
#define RVL_ERROR_HPP

#include <Rvlpch.hpp>

// statuses
#define RVL_SUCCESS         0
#define RVL_INTERNAL_ERROR  1
#define RVL_RUNTIME_ERROR   2

namespace rvl
{

    typedef unsigned short  status_t;

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

        void Print();

        static void PrintErrorS(const std::string& text);
    };
}

#endif
