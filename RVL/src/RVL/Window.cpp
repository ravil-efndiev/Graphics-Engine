#include "Window.hpp"

#include <glfw3.h>

namespace rvl
{
    Window::Window(int width, int height, const std::string &name)
    {
        _width = width;
        _height = height;
        _name = name;

        InitGlfw();
        CreateWindow();
    }

    Window::~Window()
    {
        glfwTerminate();
    }

    void Window::InitGlfw()
    {
        if (!glfwInit())
        {
            //error
        }

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    }

    void Window::CreateWindow()
    {
        _window = glfwCreateWindow(_width, _height, _name.c_str(), nullptr, nullptr);
        if (!_window)
        {
            //error
        }
        glfwMakeContextCurrent(_window);
    }

    bool Window::Closes()
    {
        return glfwWindowShouldClose(_window);
    }

    void Window::Clear(GLclampf red, GLclampf green, GLclampf blue, GLclampf alpha)
    {
        glClearColor(red, green, blue, alpha);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH);
    }
    void Window::SwapBuffers()
    {
        glfwSwapBuffers(_window);
    }
    void Window::PollEvents()
    {
        glfwPollEvents();
    }
}
