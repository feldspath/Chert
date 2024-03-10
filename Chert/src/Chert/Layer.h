#pragma once
#include "Chert/Events/Event.h"

namespace chert {
    class Layer
    {
    public:
        virtual ~Layer() = default;
        virtual void onAttach() {}
        virtual void onDetach() {}
        virtual void update() {}
        virtual void onEvent(Event& e) {}
        inline virtual bool isOverlay() const { return false; }
    };
}


