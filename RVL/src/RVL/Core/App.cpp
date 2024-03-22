#include "App.hpp"

#include "Window.hpp"
#include "ImGuiController.hpp"

#include <Events/EventListener.hpp>
#include <Rendering/Renderer/Renderer.hpp>
#include <Rendering/Renderer/ShaderLibrary.hpp>
#include <Rendering/Renderer/StandartMeshes.hpp>

#include <API/Time.hpp>
#include <API/Random.hpp>

namespace Rvl
{
    Ptr<App> App::_instance;
    
    App::App(i32 windowWidth, i32 windowHeight, const std::string& windowName)
    {
        CreateWindow(windowWidth, windowHeight, windowName);
    }

    App::~App() {}

    status App::Run()
    {
        try
        {
            EventListener::Init();
            Renderer::Init();
            Random::Init();
            StandartShaderLib::Init();            
            StandartMeshes::Init();            

            Start();
            if (_currentState) _currentState->StartScene();

            ImGuiController::Init(_window->GetWindowPtr());

            f32 timer = Time::LastTime();

            while (!_window->Closes())
            {
                RenderApi::Clear();
                Time::Update();
                ImGuiController::Update();

                Update();
                if (_currentState) _currentState->UpdateScene();

                if (_currentState)
                {
                    _currentState->Begin();
                    Render();
                    _currentState->End();
                    _currentState->PostRender();
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
            _currentState->_currentScene->OnEvent(event);
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
        RenderApi::SetClearColor(color);
    }

    void App::Close()
    {
        _window->SetClose(true);
    }

    void App::CreateWindow(i32 windowWidth, i32 windowHeight, const std::string &windowName)
    {
        _window = NewPtr<Window>(windowWidth, windowHeight, windowName);

        _window->SetEventsCallback([](Event* event)
        {
            EventListener::Listen(event);
            App::Get()->ProcessEvent(event);
        });
    }

    void App::SetCursorLocked(bool flag)
    {
        _window->SetCursorLocked(flag);
    }

    RenderMode App::GetStateRenderMode() const
    {
        return _currentState->_mode;
    }
}
