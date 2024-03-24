#pragma once

#include <functional>
#include <string>

#include "Chert/Events/Event.h"
#include "Chert/Renderer/RenderingContext.h"

namespace chert {
struct WindowProps {
    std::string title;
    unsigned int width;
    unsigned int height;

    WindowProps(const std::string &title = "Chert Engine", unsigned int width = 1280,
                unsigned int height = 720)
        : title(title), width(width), height(height) {}
};

class Window {
public:
    using EventCallbackFn = std::function<void(Event &)>;

    virtual ~Window() = default;
    virtual void update() = 0;
    virtual void setEventCallback(const EventCallbackFn &callback) = 0;
    virtual unsigned int width() const = 0;
    virtual unsigned int height() const = 0;
    virtual float aspectRatio() const = 0;
    virtual std::shared_ptr<RenderingContext> getRenderingContext() = 0;

    static std::shared_ptr<Window> create(const WindowProps &props = WindowProps());
};
} // namespace chert