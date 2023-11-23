
#include "UIModule.hpp"

#include <imgui/imgui.h>
#include <imgui/backends/imgui_impl_opengl3.h>
#include <imgui/backends/imgui_impl_glfw.h>
#include <GLFW/glfw3.h>

namespace EgorkaEngine
{
    void UIModule::on_window_creation(GLFWwindow* _window)
    {
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();

        ImGuiIO& io = ImGui::GetIO();
        io.ConfigFlags |= ImGuiConfigFlags_::ImGuiConfigFlags_DockingEnable;
        io.ConfigFlags |= ImGuiConfigFlags_::ImGuiConfigFlags_ViewportsEnable;

        ImGui_ImplOpenGL3_Init();
        ImGui_ImplGlfw_InitForOpenGL(_window, true);
    }

    void UIModule::on_window_closing()
    {
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();
    }

    void UIModule::on_draw_begining()
    {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
    }

    void UIModule::on_draw_ending()
    {
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        if (ImGui::GetIO().ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
        {
            GLFWwindow* backup_current_context = glfwGetCurrentContext();
            ImGui::UpdatePlatformWindows();
            ImGui::RenderPlatformWindowsDefault();
            glfwMakeContextCurrent(backup_current_context);
        }
    }
}