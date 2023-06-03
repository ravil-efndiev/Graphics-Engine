#include "Game.hpp"

// !!INCLUDE ONLY ONCE INSIDE CPP FILE THAT IMPLEMENTS OnInit!!
#include <RVL/Core/EntryPoint.hpp>

namespace sb
{
    using namespace rvl;

    Game::Game() : RvlApp(1000, 700, "rvl game") {}
    Game::~Game() {}

    void Game::Start()
    {
        SetClearColor({0.3f, 0.5f, 0.5f});
        _currentState = NewRef<MainScene>();
        _currentState->Start();
    }

    void Game::Update()
    {
        _currentState->Update();
    }

    void Game::Tick()
    {
        _currentState->Tick();
    }
}

rvl::Ptr<rvl::RvlApp> rvl::OnInit()
{
    return rvl::NewPtr<sb::Game>();
}
