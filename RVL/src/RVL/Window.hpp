#ifndef RVL_WINDOW_HPP
#define RVL_WINDOW_HPP

#include "Rvlpch.hpp"

class GLFWwindow;

namespace rvl
{
    class Window
    {
    public:
        Window(int width, int height, const std::string& name);
        ~Window();

        bool Closes();

        void Clear(GLclampf red = 0.f, GLclampf green = 0.f, GLclampf blue = 0.f, GLclampf alpha = 1.f);
        void SwapBuffers();
        void PollEvents();

    private:
        int _width, _height;
        std::string _name;

        GLFWwindow* _window;
        
        void InitGlfw();
        void CreateWindow();

    };
}

#endif
