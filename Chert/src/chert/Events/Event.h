#pragma once

#include <string>
#include <ostream>

#include "Chert/Core.h"

namespace chert {
    enum class EventType {
        None = 0,
        WindowResize,
        WindowClose,
        MouseMoved,
        MouseButtonPressed,
        MouseButtonReleased,
        KeyPressed,
        KeyReleased
    };

#define EVENT_CLASS_TYPE(type)  static EventType getStaticType() { return EventType::##type; }\
                                EventType getEventType() const override { return getStaticType(); }\
                                const char* getName() const override { return #type; }

    class CHERT_API Event
    {
    public:
        virtual EventType getEventType() const = 0;
        virtual const char* getName() const = 0;
        virtual std::string toString() const { return getName(); }
    };

    inline std::ostream& operator<<(std::ostream& os, const Event& e) {
        return os << e.toString();
    }
}

