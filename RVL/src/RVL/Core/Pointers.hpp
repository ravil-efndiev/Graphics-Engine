#pragma once

#include <Rvlpch.hpp>

namespace Rvl
{
    template<class T>
    using Ref = std::shared_ptr<T>;

    template<class T>
    using Ptr = std::unique_ptr<T>;

    template <class T, class ... Args>
    Ref<T> NewRef(Args&& ...args)
    {
        return std::make_shared<T>(args...);
    }

    template <class T, class ... Args>
    Ptr<T> NewPtr(Args&& ...args)
    {
        return std::make_unique<T>(args...);
    }
}

