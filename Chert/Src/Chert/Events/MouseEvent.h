#pragma once

#include "BaseEvent.h"

namespace chert {
class MouseButtonEvent : public BaseEvent {
public:
    std::string toString() const override {
        std::stringstream ss;
        ss << getName() << ": " << buttoncode;
        return ss.str();
    }

    int getButtoncode() const { return buttoncode; }

protected:
    MouseButtonEvent(int buttoncode) : buttoncode(buttoncode) {}

private:
    int buttoncode;
};

class MouseButtonPressedEvent : public MouseButtonEvent {
public:
    MouseButtonPressedEvent(int buttoncode) : MouseButtonEvent(buttoncode) {}

    EVENT_CLASS_TYPE(MouseButtonPressed)
};

class MouseButtonReleasedEvent : public MouseButtonEvent {
public:
    MouseButtonReleasedEvent(int buttoncode) : MouseButtonEvent(buttoncode) {}

    EVENT_CLASS_TYPE(MouseButtonReleased)
};

class MouseMovedEvent : public BaseEvent {
public:
    MouseMovedEvent(double xpos, double ypos) : xpos(xpos), ypos(ypos) {}

    std::string toString() const override {
        std::stringstream ss;
        ss << getName() << ": " << xpos << ", " << ypos;
        return ss.str();
    }

    double getMouseX() const { return xpos; }
    double getMouseY() const { return ypos; }

    EVENT_CLASS_TYPE(MouseMoved)

private:
    double xpos, ypos;
};

class MouseScrolledEvent : public BaseEvent {
public:
    MouseScrolledEvent(double xoffset, double yoffset) : xoffset(xoffset), yoffset(yoffset) {}

    std::string toString() const override {
        std::stringstream ss;
        ss << getName() << ": " << xoffset << ", " << yoffset;
        return ss.str();
    }

    double getXOffset() const { return xoffset; }
    double getYOffset() const { return yoffset; }

    EVENT_CLASS_TYPE(MouseScrolled)

private:
    double xoffset, yoffset;
};
} // namespace chert