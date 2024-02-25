#pragma once

#include <string>

namespace chert {
    struct WindowProps {
        std::string title;
        unsigned int width;
        unsigned int height;

        WindowProps(const std::string& title = "Chert Engine",
            unsigned int width = 800,
            unsigned int height = 600)
            : title(title), width(width), height(height) {}
    };

    class CHERT_API Window {
    public:
        virtual ~Window() {};
        virtual void update() = 0;
        virtual unsigned int getWidth() const = 0;
        virtual unsigned int getHeight() const = 0;

        static Window* create(const WindowProps& props = WindowProps());
    };
}