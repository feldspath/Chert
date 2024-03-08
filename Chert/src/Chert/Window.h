#pragma once

#include <functional>
#include <string>

#include "Chert/Events/Event.h"

namespace chert {
    struct WindowProps {
        std::string title;
        unsigned int width;
        unsigned int height;

        WindowProps(const std::string& title = "Chert Engine",
            unsigned int width = 1280,
            unsigned int height = 720)
            : title(title), width(width), height(height) {}
    };

    class Window {
    public:
        using EventCallbackFn = std::function<void(Event&)>;

        virtual ~Window() {};
        virtual void update() = 0;
        virtual unsigned int getWidth() const = 0;
        virtual unsigned int getHeight() const = 0;
        virtual void setEventCallback(const EventCallbackFn& callback) = 0;
        virtual unsigned int width() const = 0;
        virtual unsigned int height() const = 0;

        static std::unique_ptr<Window> create(const WindowProps& props = WindowProps());
    };
}