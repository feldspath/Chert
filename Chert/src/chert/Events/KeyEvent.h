#pragma once

#include <sstream>

#include "Event.h"

namespace chert {
    class KeyEvent : public Event {
    public:
        std::string toString() const override {
            std::stringstream ss;
            ss << getName() << ": " << keycode;
            return ss.str();
        }

        int getKeycode() const { return keycode; }

    protected:
        KeyEvent(int keycode) : keycode(keycode) {}

    private:
        int keycode;
    };

    class KeyPressedEvent : public KeyEvent {
    public:
        KeyPressedEvent(int keycode) : KeyEvent(keycode) {}

        EVENT_CLASS_TYPE(KeyPressed)
    };

    class KeyReleasedEvent : public KeyEvent {
    public:
        KeyReleasedEvent(int keycode) : KeyEvent(keycode) {}

        EVENT_CLASS_TYPE(KeyReleased)
    };
}