#pragma once

#include <Core/Core.hpp>

namespace Rvl {
namespace Utils
{
    template<class Base, class T>
    bool InstanceOf(const T* object)
    {
        return dynamic_cast<const Base*>(object) != nullptr;
    }

    template<class Base, class T>
    bool InstanceOf(const Ref<T>& object)
    {
        return std::dynamic_pointer_cast<Base>(object) != nullptr;
    }
}
} 

