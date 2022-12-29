#ifndef RVL_ENTRYPOINT_HPP
#define RVL_ENTRYPOINT_HPP

#include "RvlApp.hpp"
#include "Platform.hpp"

int main(int argc, char** argv)
{

    rvl::OnInit();

    if (!rvl::CurrentApp)
    {
        rvl::Error::PrintErrorS("CurrentApp is not defined");
        return RVL_RUNTIME_ERROR;
    }
    rvlStatus_t exitStatus = rvl::CurrentApp->Run();

    delete rvl::CurrentApp;

#ifdef RVL_END_IMPL

    rvl::OnEnd();

#endif

    return exitStatus;
}

#endif
