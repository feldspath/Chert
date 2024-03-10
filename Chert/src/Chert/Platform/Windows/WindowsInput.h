#pragma once

#include "Chert/Input.h"

struct GLFWwindow;

namespace chert {

    class WindowsInput : public Input {
    public:
        WindowsInput();

    protected:
        bool isKeyPressedImpl(int keycode) override;
        bool isMouseButtonPressedImpl(int button);
        std::pair<double, double> getMousePositionImpl();
        double getMouseYImpl() override;
        double getMouseXImpl() override;

    private:
        std::shared_ptr<GLFWwindow> window;
    };
}