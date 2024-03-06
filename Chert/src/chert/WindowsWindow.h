#pragma once

#include <string>

#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "Chert/Core.h"
#include "Chert/Window.h"

namespace chert {
    class WindowsWindow : public Window {
    public:
        WindowsWindow(WindowProps props);
        ~WindowsWindow() override;
        void update() override;
        inline unsigned int getWidth() const override { return data.width; }
        inline unsigned int getHeight() const override { return data.height; }
        inline void setEventCallback(const EventCallbackFn& callback) override { data.eventCallback = callback;  }
        inline GLFWwindow* getGlfwWindowPtr() { return window; }
        unsigned int width() const override;
        unsigned int height() const override;

    private:
        void init(const WindowProps& props);
        void shutdown();

        GLFWwindow* window;

        struct WindowData {
            std::string title;
            unsigned int width = 0, height = 0;
            EventCallbackFn eventCallback;
        };

        WindowData data;
    };
}