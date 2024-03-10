#include "Chert/Application.h"
#include "Chert/Platform/Windows/WindowsWindow.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"
#include "ImguiLayer.h"

namespace chert {
    void ImguiLayer::init() {
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGui::StyleColorsDark();

        ImGuiIO& io = ImGui::GetIO();
        io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
        io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;

        WindowsWindow& window = dynamic_cast<WindowsWindow&>(Application::get().getWindow());
        ImGui_ImplGlfw_InitForOpenGL(window.getGlfwWindowPtr().get(), true);
        ImGui_ImplOpenGL3_Init();
    }


    void ImguiLayer::update() {
        static bool show_demo_window = true;
        ImGui::ShowDemoWindow(&show_demo_window);
    }

    void ImguiLayer::begin() {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
    }

    void ImguiLayer::end() {
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }

    ImguiLayer::~ImguiLayer() {
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();
    }
}