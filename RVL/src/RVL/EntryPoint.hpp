#ifndef RVL_ENTRYPOINT_HPP
#define RVL_ENTRYPOINT_HPP

#include "RvlApp.hpp"

int main(int argc, char** argv)
{
    rvl::RvlApp* app = rvl::CreateApp();
    app->Run();
    delete app;

    return 0;
}

#endif
