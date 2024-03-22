#include <RVL/Core/EntryPoint.hpp>
#include "EditorApp.hpp"

int main()
{
    Rvl::status status = Rvl::InitializeApp<Rvl::EditorApp>();
    return status;
}
