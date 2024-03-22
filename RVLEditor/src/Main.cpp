#include "Editor.hpp"
#include <RVL/Core/EntryPoint.hpp>

int main()
{
    Rvl::status status = Rvl::InitializeApp<Editor>();
    return status;
}
