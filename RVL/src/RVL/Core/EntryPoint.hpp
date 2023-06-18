#pragma once

#include "App.hpp"
#include "Core.hpp"

int main(int argc, char** argv)
{

    Rvl::Ref<Rvl::App> currentApp = Rvl::OnInit();

    if (!currentApp)
    {
        Rvl::Error::PrintErrorS("CurrentApp is not defined");
        return RVL_RUNTIME_ERROR;
    }
    Rvl::status_t exitStatus = currentApp->Run();

#ifdef RVL_END_IMPL

    rvl::OnEnd();

#endif

    return exitStatus;
}

