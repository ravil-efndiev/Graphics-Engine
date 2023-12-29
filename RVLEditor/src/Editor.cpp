#include "Editor.hpp"
#include <RVL/Core/EntryPoint.hpp>

using namespace Rvl;

Editor::Editor() : App(1000, 700, "RVL Editor") {}
Editor::~Editor() {}

void Editor::Start()
{
    SetClearColor({0.22f, 0.22f, 0.27f});
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
