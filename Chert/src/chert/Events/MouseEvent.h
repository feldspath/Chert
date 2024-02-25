#pragma once

#include "Event.h"

namespace chert {
    class MouseButtonEvent : public Event {
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

    class CHERT_API MouseButtonPressedEvent : public MouseButtonEvent {
    public:
        MouseButtonPressedEvent(int buttoncode) : MouseButtonEvent(buttoncode) {}

        EVENT_CLASS_TYPE(MouseButtonPressed)
    };

    class CHERT_API MouseButtonReleasedEvent : public MouseButtonEvent {
    public:
        MouseButtonReleasedEvent(int buttoncode) : MouseButtonEvent(buttoncode) {}

        EVENT_CLASS_TYPE(MouseButtonReleased)
    };

    class CHERT_API MouseMovedEvent : public Event {
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
}