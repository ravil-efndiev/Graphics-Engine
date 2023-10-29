#pragma once
#include <Core/Core.hpp>

namespace Rvl
{
    struct IdentifierComponent
    {
        IdentifierComponent() = default;
        IdentifierComponent(const IdentifierComponent&) = default;
        IdentifierComponent(std::string name) : Name(name) {}

        std::string Name;
    };
}
