#include "WindowsInput.h"
#include "Chert/Core/Application.h"
#include "GLFW/glfw3.h"
#include "WindowsWindow.h"

namespace chert {
std::unique_ptr<Input> createInputHandler() { return std::make_unique<WindowsInput>(); }

WindowsInput::WindowsInput() {
    window = std::dynamic_pointer_cast<WindowsWindow>(Application::get().getWindow())
                 ->getGlfwWindowPtr();
}

bool WindowsInput::isKeyPressedImpl(int keycode) {
    return glfwGetKey(window, keycode) == GLFW_PRESS;
}

bool WindowsInput::isMouseButtonPressedImpl(int button) {
    return glfwGetMouseButton(window, button) == GLFW_PRESS;
}

std::pair<double, double> WindowsInput::getMousePositionImpl() {
    double xpos, ypos;
    glfwGetCursorPos(window, &xpos, &ypos);
    return {xpos, ypos};
}

double WindowsInput::getMouseXImpl() { return getMousePositionImpl().first; }

double WindowsInput::getMouseYImpl() { return getMousePositionImpl().second; }
} // namespace chert