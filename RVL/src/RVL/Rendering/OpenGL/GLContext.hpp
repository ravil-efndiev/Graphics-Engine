#ifndef RVL_GLCONTEXT_HPP
#define RVL_GLCONTEXT_HPP

struct GLFWwindow;

namespace rvl
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

#endif
