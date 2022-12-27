#include "RvlApp.hpp"
#include "EventListener.hpp"
#include "Window.hpp"

namespace rvl
{
    
    RvlApp::RvlApp(int windowWidth, int windowHeight, const std::string& windowName)
    {
        CreateWindow(windowWidth, windowHeight, windowName);
    }

    RvlApp::~RvlApp()
    {
        delete _window;
    }

    rvlStatus_t RvlApp::Run()
    {
        try
        {
            EventListener::Init();
            Start();
            while (!_window->Closes())
            {
                _window->Clear();

                Update();

                _window->SwapBuffers();
                EventListener::PollEvents();
            }
            return RVL_SUCCESS;
        }
        catch (Error error)
        {
            error.Print();
            return error._status;
        }
    }

    void RvlApp::CreateWindow(int windowWidth, int windowHeight, const std::string& windowName)
    {
        _window = new Window(windowWidth, windowHeight, windowName);

        _window->SetEventsCallback([](Event* event)
        {
            EventListener::Listen(event);
        });
    }

}
