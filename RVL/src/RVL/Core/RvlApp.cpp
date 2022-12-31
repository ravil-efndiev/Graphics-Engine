#include "RvlApp.hpp"
#include "EventListener.hpp"
#include "Window.hpp"

#include "Rendering/OpenGL/GLShaderProgram.hpp"
#include "Rendering/OpenGL/GLVertexArray.hpp"
#include "Rendering/OpenGL/GLBuffer.hpp"

#include <Rvlglpch.hpp>

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

    status_t RvlApp::Run()
    {
        try
        {
            EventListener::Init();

            GLVertexArray vao;

            std::shared_ptr<GLVertexBuffer> position (new GLVertexBuffer(
                {
                    {-0.5f, -0.5f, 0.0f},
                    {0.5f, -0.5f, 0.0f},
                    {0.5f, 0.5f, 0.0f},
                }
            ));

            std::shared_ptr<GLVertexBuffer> color (new GLVertexBuffer(
                {
                    {1.0f, 0.0f, 1.0f},
                    {0.0f, 1.0f, 1.0f},
                    {0.0f, 0.0f, 1.0f},
                }
            ));

            vao.AddVertexBuffer(position);
            vao.AddVertexBuffer(color);

            std::shared_ptr<GLIndexBuffer> ebo (new GLIndexBuffer({0, 1, 2}, 3));
            vao.AddIndexBuffer(ebo);

            GLShaderProgram prog ("../RVL/res/shaders/main.vert", "../RVL/res/shaders/main.frag");

            prog.BindAttribute(0, "position");
            prog.BindAttribute(1, "color");

            prog.Link();
            prog.Use();

            Start();
            while (!_window->Closes())
            {
                _window->Clear();
                
                vao.Draw();

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


