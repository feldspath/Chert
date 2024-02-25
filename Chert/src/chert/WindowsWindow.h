#pragma once

#include <string>

#include "GLFW/glfw3.h"
#include "Chert/Core.h"
#include "Chert/Window.h"

namespace chert {
    class CHERT_API WindowsWindow : public Window {
    public:
        WindowsWindow(WindowProps props);
        ~WindowsWindow() override;
        void update() override;
        unsigned int getWidth() const override;
        unsigned int getHeight() const override;

    private:
        void init(const WindowProps& props);
        void shutdown();

        GLFWwindow* window;

        struct WindowData {
            std::string title;
            unsigned int width, height;
        };

        WindowData data;
    };
}