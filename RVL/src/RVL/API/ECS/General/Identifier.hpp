#pragma once
#include <Core/Core.hpp>

namespace Rvl
{
    struct Identifier
    {
        Identifier() = default;
        Identifier(const Identifier&) = default;
        Identifier(std::string name) : Name(name) {}

        std::string Name;
    };
}
