#include "ImguiLayer.h"
#include "Chert/Core/Application.h"
#include "Platform/Windows/WindowsWindow.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"

namespace chert {
void ImguiLayer::onAttach() {
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui::StyleColorsDark();

    ImGuiIO &io = ImGui::GetIO();
    io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
    io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;

    auto window = std::dynamic_pointer_cast<WindowsWindow>(Application::get().getWindow());
    ImGui_ImplGlfw_InitForOpenGL(window->getGlfwWindowPtr(), true);
    ImGui_ImplOpenGL3_Init();
}

void ImguiLayer::render() { ImGui::Render(); }

void ImguiLayer::begin() {
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
}

void ImguiLayer::end() { ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData()); }

void ImguiLayer::onDetach() {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}
} // namespace chert