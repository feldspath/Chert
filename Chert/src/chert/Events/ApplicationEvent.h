#pragma once

#include <sstream>

#include "Event.h"

namespace chert {
    class WindowCloseEvent : public Event {
    public:
        EVENT_CLASS_TYPE(WindowClose)
    };

    class WindowResizeEvent : public Event {
    public:
        WindowResizeEvent(unsigned int width, unsigned int height) : width(width), height(height) {}

        std::string toString() const override {
            std::stringstream ss;
            ss << getName() << ": " << width << "," << height;
            return ss.str();
        }

        EVENT_CLASS_TYPE(WindowResize)

    private:
        unsigned width, height;
    };
}