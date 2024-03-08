#pragma once

#include <variant>

#include "Chert/Events/ApplicationEvent.h"
#include "Chert/Events/KeyEvent.h"
#include "Chert/Events/MouseEvent.h"

namespace chert {
    using Event = std::variant<WindowCloseEvent,
        WindowResizeEvent,
        KeyPressedEvent,
        KeyReleasedEvent,
        MouseButtonPressedEvent,
        MouseButtonReleasedEvent,
        MouseMovedEvent>;

    class EventDispatcher {
        template <typename T>
        using EventDispatcherFn = std::function<bool(T&)>;

    public:
        EventDispatcher(Event& e) : event(e) {}

        template <typename T>
        bool dispatch(EventDispatcherFn<T> f) const {
            if (std::holds_alternative<T>(event)) {
                bool handled = f(std::get<T>(event));
                std::visit([handled](auto&& e) {
                    e.handled = handled;
                    }, event);
                return true;
            }
            return false;
        }

    private:
        Event& event;
    };

    inline std::ostream& operator<<(std::ostream& os, const Event& e) {
        std::string s = std::visit([](auto&& e) -> std::string {
            return e.toString();
            }, e);
        return os << s;
    }

#define CHERT_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)
}