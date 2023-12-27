#include "Rvlglpch.hpp"

#include "GLContext.hpp"
#include <Core/Core.hpp>

namespace Rvl
{
    GLContext::GLContext(GLFWwindow *pwindow)
    {
        _pwindow = pwindow;

        glfwMakeContextCurrent(_pwindow);
        InitGlad();
     
        glEnable(GL_DEPTH_TEST);
        glEnable(GL_BLEND);
        glEnable(GL_MULTISAMPLE);  
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
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
