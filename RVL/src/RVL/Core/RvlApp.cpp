#include "RvlApp.hpp"
#include "EventListener.hpp"
#include "Window.hpp"

#include "Rendering/OpenGL/GLShaderProgram.hpp"
#include "Rendering/OpenGL/GLVertexArray.hpp"
#include "Rendering/OpenGL/GLBuffer.hpp"

#include "Rendering/Renderer/Renderer.hpp"
#include "Rendering/Renderer/PerspectiveCamera.hpp"
#include "Rendering/Renderer/OrthographicCamera.hpp"

#include "API/Time.hpp"

#include <Rvlglpch.hpp>

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
            Start();

            while (!_window->Closes())
            {
                Renderer::Clear(_clearColor[0], _clearColor[1], _clearColor[2], _clearColor[3]);
                Time::Update();

                Update();
                _currentScene->MakeScene();
                Render();

                _window->SwapBuffers();
                EventListener::PollEvents();
            }
            return RVL_SUCCESS;
        }
        catch (Error error)
        {
            error.Print();
            return error.Status;
        }
    }

    void RvlApp::SetClearColor(GLclampf red, GLclampf green, GLclampf blue, GLclampf alpha)
    {
        _clearColor = {red, green, blue, alpha};
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
