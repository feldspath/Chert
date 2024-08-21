#pragma once

#include <sstream>

#include "BaseEvent.h"

namespace chert {
class WindowCloseEvent : public BaseEvent {
public:
    EVENT_CLASS_TYPE(WindowClose)
};

class WindowResizeEvent : public BaseEvent {
public:
    WindowResizeEvent(unsigned int width, unsigned int height) : width(width), height(height) {}

    std::string toString() const override {
        std::stringstream ss;
        ss << getName() << ": " << width << "," << height;
        return ss.str();
    }

    inline unsigned int getWidth() const { return width; }
    inline unsigned int getHeight() const { return height; }

    EVENT_CLASS_TYPE(WindowResize)

private:
    unsigned width, height;
};
} // namespace chert