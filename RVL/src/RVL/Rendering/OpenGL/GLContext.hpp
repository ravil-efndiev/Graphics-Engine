#pragma once

struct GLFWwindow;

namespace Rvl
{
    class GLContext
    {
    public:
        GLContext(GLFWwindow* pwindow);
        ~GLContext();

        void SwapBuffers();

    private:
        GLFWwindow* _pwindow;

        void InitGlad();
    };
}

