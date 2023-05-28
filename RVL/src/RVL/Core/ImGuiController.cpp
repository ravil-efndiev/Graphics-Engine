#include "ImGuiController.hpp"
#include <Rendering/Renderer/Renderer.hpp>

namespace rvl
{
    void ImGuiController::Init(GLFWwindow* glfwWindow)
    {
        IMGUI_CHECKVERSION();
            
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO();

        io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;
        io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

        ImGui::StyleColorsDark();

        ImGui_ImplGlfw_InitForOpenGL(glfwWindow, true);
        ImGui_ImplOpenGL3_Init("#version 330");

        io.FontDefault = io.Fonts->AddFontFromFileTTF("./assets/fonts/FixelText-Medium.ttf", 14.f);
    }
    
    void ImGuiController::Shutdown()
    {
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();
    }

    void ImGuiController::Update()
    {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
    }
    
    void ImGuiController::Render()
    {
        ImGuiIO& io = ImGui::GetIO();

        int viewport[2];
        Renderer::GetViewport(viewport);

		io.DisplaySize = ImVec2((float)viewport[1], (float)viewport[2]);

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			GLFWwindow* backup_current_context = glfwGetCurrentContext();
			ImGui::UpdatePlatformWindows();
			ImGui::RenderPlatformWindowsDefault();
			glfwMakeContextCurrent(backup_current_context);
		}
    }

}
