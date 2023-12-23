#pragma once

#include <Rvlglpch.hpp>

namespace Rvl
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

