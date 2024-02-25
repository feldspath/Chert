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
        inline unsigned int getWidth() const override { return data.width; }
        inline unsigned int getHeight() const override { return data.height; }
        inline void setEventCallback(const EventCallbackFn& callback) override { data.eventCallback = callback;  }

    private:
        void init(const WindowProps& props);
        void shutdown();

        GLFWwindow* window;

        struct WindowData {
            std::string title;
            unsigned int width, height;
            EventCallbackFn eventCallback;
        };

        WindowData data;
    };
}