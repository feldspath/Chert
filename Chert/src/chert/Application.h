#pragma once

#include <memory>

#include "Chert/Core.h"
#include "Chert/Window.h"

namespace chert {
    class CHERT_API Application
    {
    public:
        Application();
        Application(WindowProps windowProps);
        void run();

    private:
        std::unique_ptr<Window> window;
    };

    Application* CreateApplication();
}
