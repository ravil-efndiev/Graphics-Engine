#include "Rvlglpch.hpp"

#include "GLContext.hpp"
#include <Core/Core.hpp>

namespace rvl
{
    GLContext::GLContext(GLFWwindow *pwindow)
    {
        _pwindow = pwindow;

        glfwMakeContextCurrent(_pwindow);
        InitGlad();
        glEnable(GL_DEPTH_TEST);
    }

    GLContext::~GLContext()
    {
    }

    void GLContext::SwapBuffers()
    {
        glfwSwapBuffers(_pwindow);
    }

    void GLContext::InitGlad()
    {
        auto gladInitSuccess = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
        RVL_ASSERT(gladInitSuccess, "failed to init glad")
    }
}
