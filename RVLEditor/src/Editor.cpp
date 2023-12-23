#include "Editor.hpp"
#include <RVL/Core/EntryPoint.hpp>

using namespace Rvl;

RVL_IMPL_INIT(Editor);

Editor::Editor() : App(1000, 700, "RVL Editor") {}
Editor::~Editor() {}

void Editor::Start()
{
    SetClearColor({0.10f, 0.10f, 0.12f});
    _currentState = NewPtr<EditorState>();
    _currentState->Start();
}

void Editor::Update()
{
    _currentState->Update();
}

void Editor::Tick()
{
    _currentState->Tick();
}
