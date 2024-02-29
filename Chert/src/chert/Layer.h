#pragma once
#include "Chert/Events/Event.h"

namespace chert {
    class Layer
    {
    public:
        virtual void onAttach() {}
        virtual void onDetach() {}
        virtual void update() {}
        virtual void onEvent(Event& e) {}
        inline virtual bool isOverlay() const { return false; }
    };

    class Overlay : public Layer
    {
    public:
        inline bool isOverlay() const final { return true; }
    };
}


