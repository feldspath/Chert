#pragma once

#include <string>

#include "Chert/Core.h"
#include "Chert/Window.h"
#include "Chert/Renderer/RenderingContext.h"

struct GLFWwindow;

namespace chert {
    class WindowsWindow : public Window {
    public:
        WindowsWindow(WindowProps props);
        ~WindowsWindow() override;
        void update() override;
        inline unsigned int getWidth() const override { return data.width; }
        inline unsigned int getHeight() const override { return data.height; }
        inline void setEventCallback(const EventCallbackFn& callback) override { data.eventCallback = callback;  }
        inline std::shared_ptr<GLFWwindow> getGlfwWindowPtr() { return window; }
        inline RenderingContext& getRenderingContext() override { return *renderingContext; }
        unsigned int width() const override;
        unsigned int height() const override;

    private:
        void init(const WindowProps& props);
        void shutdown();

        std::shared_ptr<GLFWwindow> window;

        struct WindowData {
            std::string title;
            unsigned int width = 0, height = 0;
            EventCallbackFn eventCallback;
        };

        WindowData data;
        std::unique_ptr<RenderingContext> renderingContext;
    };
}