#include "RvlApp.hpp"

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

    void RvlApp::Run()
    {
        Start();
        while (!_window->Closes())
        {
            _window->Clear();

            Update();

            _window->SwapBuffers();
            _window->PollEvents();
        }
    }

    void RvlApp::CreateWindow(int windowWidth, int windowHeight, const std::string& windowName)
    {
        _window = new Window(windowWidth, windowHeight, windowName);
    }

}


