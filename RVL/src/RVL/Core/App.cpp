#include "App.hpp"

#include "Window.hpp"
#include "ImGuiController.hpp"

#include <Events/EventListener.hpp>
#include <Rendering/Renderer/Renderer.hpp>

#include <API/Time.hpp>
#include <API/Random.hpp>

namespace Rvl
{
    Ref<App> App::_instance = nullptr;
    
    App::App(int windowWidth, int windowHeight, const std::string& windowName)
    {
        CreateWindow(windowWidth, windowHeight, windowName);
    }

    App::~App() { }

    status_t App::Run()
    {
        try
        {
            EventListener::Init();
            Renderer::Init();
            Random::Init();
            
            Start();
            if (_currentState) _currentState->StartScene();

            ImGuiController::Init(_window->GetWindowPtr());

            float timer = Time::LastTime();

            while (!_window->Closes())
            {
                RenderCommand::Clear();
                Time::Update();
                ImGuiController::Update();

                Update();
                if (_currentState) _currentState->UpdateScene();

                if (_currentState)
                {
                    _currentState->Begin();
                    Render();
                    _currentState->End();
                }

                ImGuiController::Render();

                _window->SwapBuffers();
                EventListener::PollEvents();

                if (Time::Current() - timer > Time::FixedDeltaTime())
                {
                    timer += Time::FixedDeltaTime();
                    Tick();
                }
            }

            Renderer::Shutdown();
            ImGuiController::Shutdown();

            return RVL_SUCCESS;
        }
        catch (Error error)
        {
            error.Print();
            return error.Status;
        }
    }

    void App::ProcessEvent(Event* event)
    {
        if (_currentState)
        {
            _currentState->_currentScene.OnEvent(event);
        }
    }

    void App::Start() {}
    void App::Update() {}
    void App::Tick() {}

    void App::Render()
    {
        _currentState->Render();
    }

    void App::SetClearColor(const glm::vec3& color)
    {
        RenderCommand::SetClearColor(color);
    }

    void App::Close()
    {
        _window->SetClose(true);
    }

    void App::CreateWindow(int windowWidth, int windowHeight, const std::string &windowName)
    {
        _window = NewPtr<Window>(windowWidth, windowHeight, windowName);

        _window->SetEventsCallback([](Event* event)
        {
            EventListener::Listen(event);
            App::GetInstance()->ProcessEvent(event);
        });
    }

    void App::SetCursorLocked(bool flag)
    {
        _window->SetCursorLocked(flag);
    }
}
