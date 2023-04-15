#include "Window.hpp"

#include "Rendering/OpenGL/GLContext.hpp"
#include "Rvlglpch.hpp"

namespace rvl
{
    Window::Window(int width, int height, const std::string &name)
    {
        _width = width;
        _height = height;
        _name = name;

        InitGlfw();
        CreateWindow();
        SetCallbacks();
    }

    Window::~Window()
    {
        glfwTerminate();
    }

    void Window::InitGlfw()
    {
        auto initSuccess = glfwInit();
        RVL_ASSERT(initSuccess, "failed to init GLFW")

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    }

    void Window::CreateWindow()
    {
        _window = glfwCreateWindow(_width, _height, _name.c_str(), nullptr, nullptr);
        RVL_ASSERT(_window, "failed to create GLFW window")

        _context = std::make_unique<GLContext>(_window);
    }

    void Window::SetCallbacks()
    {
        glfwSetWindowUserPointer(_window, &_eventCallback);

        glfwSetWindowSizeCallback(_window, [](GLFWwindow *window, int width, int height) {
            EventCallbackStruct* callback = static_cast<EventCallbackStruct*>(glfwGetWindowUserPointer(window));

            WindowResizeEvent event (width, height);

            callback->EventCallback(&event);
        });

        glfwSetKeyCallback(_window, [](GLFWwindow* window, int key, int scancode, int action, int mode) 
        {
            EventCallbackStruct* callback = static_cast<EventCallbackStruct*>(glfwGetWindowUserPointer(window));

            if (action == GLFW_PRESS)
            {
                KeyPressEvent event (key);
                callback->EventCallback(&event);
            }
            else if (action == GLFW_RELEASE)
            {
                KeyReleaseEvent event (key);
                callback->EventCallback(&event);
            }
        });
    }

    bool Window::Closes()
    {
        return glfwWindowShouldClose(_window);
    }

    void Window::SwapBuffers()
    {
        _context->SwapBuffers();
    }
    void Window::PollEvents()
    {
        glfwPollEvents();
    }

    void Window::SetEventsCallback(void (*eventCallback)(Event *))
    {
        _eventCallback.EventCallback = eventCallback;
    }

    int Window::GetWidth() const
    {
        return _width;
    }

    int Window::GetHeight() const
    {
        return _height;
    }
}
