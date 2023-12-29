#include "Game.hpp"
#include <RVL/Core/EntryPoint.hpp>

int main()
{
    Rvl::status_t status = Rvl::InitializeApp<Game>(1200, 800, "Sandbox");
    return status;   
}
