#include "Game.hpp"

// !!INCLUDE ONLY ONCE INSIDE CPP FILE THAT IMPLEMENTS OnInit!!
#include <RVL/Core/EntryPoint.hpp>

namespace name
{
    using namespace rvl;

    Game::Game() : RvlApp(1000, 700, "rvl game") {}
    Game::~Game() {}

    void Game::Start()
    {
        SetClearColor(0.3f, 0.5f, 0.5f, 1.f);
        _currentScene = CreateRef<MainScene>();
        _currentScene->Start();
    }

    void Game::Update()
    {
        _currentScene->Update();
    }

    void Game::Render()
    {
        _currentScene->Render();
    }
}

rvl::Scope<rvl::RvlApp> rvl::OnInit()
{
    return rvl::CreateScope<name::Game>();
}
