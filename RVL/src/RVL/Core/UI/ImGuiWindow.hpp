#pragma once
#include "Core/Core.hpp"

namespace Rvl
{
    class ImGuiWindow
    {
    public:
        virtual void ImGuiRender() = 0;

        virtual void SetName(const std::string& name) = 0;
        virtual std::string GetName() const = 0;
    };
}

