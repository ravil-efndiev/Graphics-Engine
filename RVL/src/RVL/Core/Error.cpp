#include "Error.hpp"

namespace rvl
{
    void rvl::Error::Print()
    {
        if (Status == RVL_RUNTIME_ERROR)
            std::cerr << "RUNTIME_ERROR => " << Text << std::endl;
        else if (Status == RVL_INTERNAL_ERROR)
            std::cerr << "INTERNAL_ERROR => " << Text << std::endl;
    }

    void Error::PrintErrorS(const std::string &text)
    {
        std::cerr << "RUNTIME_ERROR => " << text << std::endl;
    }
}