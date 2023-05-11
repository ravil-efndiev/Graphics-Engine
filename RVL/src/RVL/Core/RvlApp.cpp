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

            while (!_window->Closes())
            {
                Renderer::Clear();
                Time::Update();
                ImGuiController::Update();

                Update();

                if (_currentScene)
                {
                    _currentScene->Begin();
                    _currentScene->Render();
                    _currentScene->End();
                }

                ImGuiController::Render();

                _window->SwapBuffers();
                EventListener::PollEvents();
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

    void RvlApp::SetClearColor(const glm::vec3& color)
    {
        Renderer::SetClearColor(color);
    }

    void RvlApp::CreateWindow(int windowWidth, int windowHeight, const std::string &windowName)
    {
        _window = std::make_unique<Window>(windowWidth, windowHeight, windowName);

        _window->SetEventsCallback([](Event* event)
        {
            EventListener::Listen(event);
        });
    }

}
