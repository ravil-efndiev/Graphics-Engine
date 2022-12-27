#ifndef RVL_ENTRYPOINT_HPP
#define RVL_ENTRYPOINT_HPP

#include "RvlApp.hpp"

int main(int argc, char** argv)
{
    rvl::OnInit();

    rvl::CurrentApp->Run();

    delete rvl::CurrentApp;
    return 0;
}

#endif
