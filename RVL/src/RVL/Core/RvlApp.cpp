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
            Start();

            GLVertexArray squareVao;

            std::shared_ptr<GLVertexBuffer> squarePos (new GLVertexBuffer(
                {
                    {-0.8f, -0.8f, 0.0f},
                    {0.8f, -0.8f, 0.0f},
                    {0.8f, 0.8f, 0.0f},
                    {-0.8f, 0.8f, 0.0f},
                }
            ));

            std::shared_ptr<GLIndexBuffer> squareEbo (new GLIndexBuffer({0, 1, 2, 2, 3, 0}));

            squareVao.AddVertexBuffer(squarePos);
            squareVao.AddIndexBuffer(squareEbo);


            GLVertexArray triangleVao;

            std::shared_ptr<GLVertexBuffer> trianglePos (new GLVertexBuffer(
                {
                    {-0.5f, -0.5f, 0.0f},
                    {0.5f, -0.5f, 0.0f},
                    {0.0f, 0.5f, 0.0f},
                }
            ));

            std::shared_ptr<GLVertexBuffer> triangleColor (new GLVertexBuffer(
                {
                    {1.0f, 0.3f, 0.3f},
                    {1.0f, 0.0f, 0.7f},
                    {1.0f, 0.0f, 0.0f},
                }
            ));

            std::shared_ptr<GLIndexBuffer> triangleEbo (new GLIndexBuffer({0, 1, 2}));

            triangleVao.AddVertexBuffer(trianglePos);
            triangleVao.AddVertexBuffer(triangleColor);

            triangleVao.AddIndexBuffer(triangleEbo);


            GLShaderProgram squareProg ("../RVL/res/shaders/background.vert", "../RVL/res/shaders/background.frag");

            squareProg.BindAttribute(0, "position");
            squareProg.Link();

            GLShaderProgram triangleProg ("../RVL/res/shaders/main.vert", "../RVL/res/shaders/main.frag");

            triangleProg.BindAttribute(0, "position");
            triangleProg.BindAttribute(1, "color");

            triangleProg.Link();

            while (!_window->Closes())
            {
                _window->Clear();
            
                Update();

                triangleProg.Use();
                triangleVao.Draw();

                squareProg.Use();
                squareVao.Draw();

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

    void RvlApp::CreateWindow(int windowWidth, int windowHeight, const std::string& windowName)
    {
        _window = new Window(windowWidth, windowHeight, windowName);

        _window->SetEventsCallback([](Event* event)
        {
            EventListener::Listen(event);
        });
    }

}


