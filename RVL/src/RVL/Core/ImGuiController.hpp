#ifndef RVL_IMGUICONTROLLER_HPP
#define RVL_IMGUICONTROLLER_HPP

#include <Rvlglpch.hpp>

namespace rvl
{
    class ImGuiController
    {
    public:
        static void Init(GLFWwindow* glfwWindow);
        static void Shutdown();
        static void Update();
        static void Render();
    };
}

#endif
