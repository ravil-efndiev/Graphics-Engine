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
        /*
        OrthographicCamera cam ({0.f, 0.f, 0.f}, 10.f);

        int viewport[2];
        Renderer::GetViewport(viewport);
        Renderer::CreateScene(cam, viewport[0], viewport[1]);

        Renderer::DrawRect({{0.f, 0.f, 0.f}, 0.f, {2.f, 2.f}}, {1.f, 1.f, 1.f});

        Renderer::ShutdownScene();
        */
    }
}

rvl::Scope<rvl::RvlApp> rvl::OnInit()
{
    return rvl::CreateScope<name::Game>();
}
