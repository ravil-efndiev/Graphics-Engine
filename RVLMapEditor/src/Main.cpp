#include <RVL/Core/EntryPoint.hpp>
#include "EditorApp.hpp"

int main()
{
    Rvl::status_t status = Rvl::InitializeApp<Rvl::EditorApp>();
    return status;
}
