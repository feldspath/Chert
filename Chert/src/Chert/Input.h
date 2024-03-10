#pragma once

#include <memory>
#include "Chert/Log.h"

namespace chert {
    class Input;

    class Input {
    public:
        virtual ~Input() = default;
        static void init();
        inline static bool isKeyPressed(int keycode) { return instance->isKeyPressedImpl(keycode); }
        inline static bool isMouseButtonPressed(int button) { return instance->isMouseButtonPressedImpl(button); }
        inline static std::pair<double, double> getMousePosition() { return instance->getMousePositionImpl(); }
        inline static double getMouseX() { return instance->getMouseXImpl(); }
        inline static double getMouseY() { return instance->getMouseYImpl(); }

    protected:
        virtual bool isKeyPressedImpl(int keycode) = 0;
        virtual bool isMouseButtonPressedImpl(int button) = 0;
        virtual std::pair<double, double> getMousePositionImpl() = 0;
        virtual double getMouseYImpl() = 0;
        virtual double getMouseXImpl() = 0;

    private:
        static std::unique_ptr<Input> instance;
    };

    std::unique_ptr<Input> createInputHandler();
}