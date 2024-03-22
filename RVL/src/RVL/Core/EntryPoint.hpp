#pragma once

#include "App.hpp"
#include "Core.hpp"

namespace Rvl
{
    template<class T, class... Args>
    status InitializeApp(Args&& ...args)
    {
        App* currentApp = App::New<T>(std::forward<Args>(args)...);

        if (!currentApp)
        {
            Error::PrintErrorS("CurrentApp is not defined");
            return RVL_RUNTIME_ERROR;
        }

        status exitStatus = currentApp->Run();
        return exitStatus;
    }
}
