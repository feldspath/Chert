#pragma once

#include <functional>
#include <ostream>
#include <string>

#include "Chert/Core/Core.h"

namespace chert {
enum class EventType {
    None = 0,
    WindowResize,
    WindowClose,
    MouseMoved,
    MouseButtonPressed,
    MouseButtonReleased,
    MouseScrolled,
    KeyPressed,
    KeyReleased
};

#define EVENT_CLASS_TYPE(type)                                                                     \
    static EventType getStaticType() { return EventType::##type; }                                 \
    EventType getEventType() const override { return getStaticType(); }                            \
    const char *getName() const override { return #type "Event"; }

class BaseEvent {
    friend class EventDispatcher;

public:
    virtual EventType getEventType() const = 0;
    virtual const char *getName() const = 0;
    virtual std::string toString() const { return getName(); }
    bool isHandled() const { return handled; }

private:
    bool handled = false;
};
} // namespace chert
