#include "Error.hpp"

#include "Macros.hpp"

namespace Rvl
{
    void Error::Print()
    {
        switch (Status) 
        {
        case RVL_RUNTIME_ERROR:
            std::cerr << RVL_LOG_COLOR_RED << "RUNTIME ERROR => " << Text << RVL_LOG_COLOR_NONE << std::endl;
            break;
        case RVL_INTERNAL_ERROR:
            std::cerr << RVL_LOG_COLOR_RED << "INTERNAL ERROR => " << Text << RVL_LOG_COLOR_NONE << std::endl;
            break;
        case RVL_CLIENT_ERROR:
            std::cerr << RVL_LOG_COLOR_RED << "ERROR THROWN BY CLIENT => " << Text << RVL_LOG_COLOR_NONE << std::endl;
            break;
        default:
            std::cerr << RVL_LOG_COLOR_RED << "unknown error type => " << Text << RVL_LOG_COLOR_NONE << std::endl;
            break;
        }
    }

    void Error::PrintErrorS(const std::string &text)
    {
        std::cerr << RVL_LOG_COLOR_RED << "RUNTIME_ERROR => " << text << RVL_LOG_COLOR_NONE << std::endl;
    }
}
