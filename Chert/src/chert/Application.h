#pragma once

#include <memory>

#include "Chert/Core.h"
#include "Chert/Window.h"
#include "Chert/Events/ApplicationEvent.h"

namespace chert {
    class Application
    {
    public:
        Application(WindowProps windowProps);
        void run();
        void onEvent(Event& e);
        bool onWindowClose(const WindowCloseEvent& e);

    private:
        std::unique_ptr<Window> window;
        bool running = true;
    };

    Application* CreateApplication();
}
