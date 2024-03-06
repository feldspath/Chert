#pragma once

#include "Chert/Layer.h"
#include "Chert/Application.h"
#include "Chert/Platform/Windows/WindowsWindow.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"

namespace chert {
    class ImguiLayer : public Layer {
        
    public:
        void onAttach() override {
            IMGUI_CHECKVERSION();
            ImGui::CreateContext();
            ImGui::StyleColorsDark();

            ImGuiIO& io = ImGui::GetIO();
            io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
            io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;

            const char* glsl_version = "#version 460";
            WindowsWindow& window = dynamic_cast<WindowsWindow&>(Application::get().getWindow());
            ImGui_ImplGlfw_InitForOpenGL(window.getGlfwWindowPtr(), true);
            ImGui_ImplOpenGL3_Init(glsl_version);
        }

        void update() override {
            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplGlfw_NewFrame();
            ImGui::NewFrame();

            static bool show_demo_window = true;
            ImGui::ShowDemoWindow(&show_demo_window);

            ImGui::Render();
            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        }

        void onDetach() override {
            ImGui_ImplOpenGL3_Shutdown();
            ImGui_ImplGlfw_Shutdown();
            ImGui::DestroyContext();
        }

    private:
        float time = 0.0f;
    };
}