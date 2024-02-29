#pragma once

#include <functional>
#include <ostream>
#include <string>

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
                                const char* getName() const override { return #type "Event"; }

    class Event {
        friend class EventDispatcher;

    public:
        virtual EventType getEventType() const = 0;
        virtual const char* getName() const = 0;
        virtual std::string toString() const { return getName(); }
        bool isHandled() const { return handled; }

    private:
        bool handled = false;
    };

    class EventDispatcher {
        template <typename T>
        using EventDispatcherFn = std::function<bool(T&)>;

    public:
        EventDispatcher(Event& e) : event(e) {}

        template <typename T>
        bool dispatch(EventDispatcherFn<T> f) const {
            if (T::getStaticType() == event.getEventType()) {
                event.handled = f(*(T*)&event);
                return true;
            }
            return false;
        }

    private:
        Event& event;
    };

    inline std::ostream& operator<<(std::ostream& os, const Event& e) {
        return os << e.toString();
    }
}

