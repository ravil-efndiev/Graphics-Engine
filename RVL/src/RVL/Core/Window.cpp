#include "Window.hpp"

#include "Rendering/OpenGL/GLContext.hpp"
#include "Rvlglpch.hpp"

namespace Rvl
{
    Window::Window(i32 width, i32 height, const std::string &name)
        : _name(name)
    {
        InitGlfw();
        CreateWindow(width, height);
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

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_SAMPLES, 4);
    }

    void Window::CreateWindow(i32 width, i32 height)
    {
        _window = glfwCreateWindow(width, height, _name.c_str(), nullptr, nullptr);
        RVL_ASSERT(_window, "failed to create GLFW window")

        _context = NewPtr<GLContext>(_window);
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

        glfwSetMouseButtonCallback(_window, [](GLFWwindow* window, int button, int action, int mode)
        {
            EventCallbackStruct* callback = static_cast<EventCallbackStruct*>(glfwGetWindowUserPointer(window));

            if (action == GLFW_PRESS)
            {
                MouseButtonPressEvent event (button);
                callback->EventCallback(&event);
            }
            else if (action == GLFW_RELEASE)
            {
                MouseButtonReleaseEvent event (button);
                callback->EventCallback(&event);
            }
        });

        glfwSetCursorPosCallback(_window, [](GLFWwindow* window, double x, double y) 
        {
            EventCallbackStruct* callback = static_cast<EventCallbackStruct*>(glfwGetWindowUserPointer(window));

            CursorPosEvent event (x, y);
            callback->EventCallback(&event);
        });

    }

    bool Window::Closes() const
    {
        return glfwWindowShouldClose(_window);
    }

    void Window::SetClose(bool value)
    {
        glfwSetWindowShouldClose(_window, value);
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

    GLFWwindow* Window::GetWindowPtr()
    {
        return _window;
    }
    
    void Window::SetCursorLocked(bool flag)
    {
        glfwSetInputMode(_window, GLFW_CURSOR, flag ? GLFW_CURSOR_DISABLED : GLFW_CURSOR_NORMAL);
    }
}
