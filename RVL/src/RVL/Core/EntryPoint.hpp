#pragma once

#include "App.hpp"
#include "Core.hpp"

namespace Rvl
{
    template<class T, class... Args>
    Rvl::status_t InitializeApp(Args&& ...args)
    {
        Rvl::Ref<Rvl::App> currentApp = App::New<T>(args...);

        if (!currentApp)
        {
            Rvl::Error::PrintErrorS("CurrentApp is not defined");
            return RVL_RUNTIME_ERROR;
        }
        Rvl::status_t exitStatus = currentApp->Run();
        return exitStatus;
    }
}
