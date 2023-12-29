#include "Editor.hpp"
#include <RVL/Core/EntryPoint.hpp>

int main()
{
    Rvl::status_t status = Rvl::InitializeApp<Editor>();
    return status;
}
