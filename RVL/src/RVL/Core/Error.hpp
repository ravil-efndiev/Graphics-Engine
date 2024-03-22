#pragma once

#include <Rvlpch.hpp>

#define RVL_SUCCESS         0
#define RVL_INTERNAL_ERROR  1
#define RVL_RUNTIME_ERROR   2

// must be thrown and caught by client
// is not processed by engine
#define RVL_CLIENT_ERROR    3

namespace Rvl
{

    typedef unsigned short  status;

    struct Error
    {   
        std::string Text;
        status Status;
        Error(const std::string& text, status status_) : Text(text), Status(status_) {}

        void Print();

        static void PrintErrorS(const std::string& text);
    };
}

