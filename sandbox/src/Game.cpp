#include "Game.hpp"

// !!INCLUDE ONLY ONCE INSIDE CPP FILE THAT IMPLEMENTS OnInit!!
#include <RVL/Core/EntryPoint.hpp>

#include <Rendering/Renderer/Renderer.hpp>
#include <Rendering/Renderer/OrthographicCamera.hpp>

namespace name
{
    using namespace rvl;

    Game::Game() : RvlApp(1000, 700, "rvl game") {}
    Game::~Game() {}

    void Game::Start()
    {
        SetClearColor({0.3f, 0.5f, 0.5f});
        _currentScene = CreateRef<MainScene>();
        _currentScene->Start();
    }

    void Game::Update()
    {
        _currentScene->Update();

        ImGui::Begin("wnd");
        ImGui::End();
    }
}

rvl::Ptr<rvl::RvlApp> rvl::OnInit()
{
    return rvl::CreatePtr<name::Game>();
}
