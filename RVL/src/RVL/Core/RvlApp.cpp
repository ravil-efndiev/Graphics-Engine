#include "RvlApp.hpp"

#include "Window.hpp"
#include "ImGuiController.hpp"

#include <Events/EventListener.hpp>
#include <Rendering/Renderer/Renderer.hpp>

#include <API/Time.hpp>
#include <API/Random.hpp>

namespace rvl
{
    
    RvlApp::RvlApp(int windowWidth, int windowHeight, const std::string& windowName)
    {
        CreateWindow(windowWidth, windowHeight, windowName);
    }

    RvlApp::~RvlApp() { }

    status_t RvlApp::Run()
    {
        try
        {
            EventListener::Init();
            Renderer::Init();
            Random::Init();
            
            Start();

            ImGuiController::Init(_window->GetWindowPtr());

            float timer = Time::LastTime();

            while (!_window->Closes())
            {
                Renderer::Clear();
                Time::Update();
                ImGuiController::Update();

                Update();

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

    void RvlApp::Tick() {}

    void RvlApp::Render()
    {
        _currentState->Render();
    }

    void RvlApp::SetClearColor(const glm::vec3& color)
    {
        Renderer::SetClearColor(color);
    }

    void RvlApp::Close()
    {
        _window->SetClose(true);
    }

    void RvlApp::CreateWindow(int windowWidth, int windowHeight, const std::string &windowName)
    {
        _window = NewPtr<Window>(windowWidth, windowHeight, windowName);

        _window->SetEventsCallback([](Event* event)
        {
            EventListener::Listen(event);
        });
    }

}
