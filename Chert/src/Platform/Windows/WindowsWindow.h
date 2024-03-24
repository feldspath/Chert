#pragma once

#include <string>

#include "Chert/Core/Core.h"
#include "Chert/Core/Window.h"
#include "Chert/Renderer/RenderingContext.h"

struct GLFWwindow;

namespace chert {
class WindowsWindow : public Window {
public:
    WindowsWindow(WindowProps props);
    ~WindowsWindow() override;
    void update() override;
    inline void setEventCallback(const EventCallbackFn &callback) override {
        data.eventCallback = callback;
    }
    inline GLFWwindow *getGlfwWindowPtr() { return window; }
    inline std::shared_ptr<RenderingContext> getRenderingContext() override {
        return renderingContext;
    }
    inline unsigned int width() const override { return data.width; }
    inline unsigned int height() const override { return data.height; }
    inline float aspectRatio() const {
        return static_cast<float>(data.width) / static_cast<float>(data.height);
    }

private:
    void init(const WindowProps &props);
    void shutdown();

    GLFWwindow *window;

    struct WindowData {
        std::string title;
        unsigned int width = 0, height = 0;
        EventCallbackFn eventCallback;
    };

    WindowData data;
    std::shared_ptr<RenderingContext> renderingContext;
};
} // namespace chert