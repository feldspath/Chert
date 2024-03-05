#pragma once

#include <memory>

#include "Chert/Core.h"
#include "Chert/Window.h"
#include "Chert/Events/Event.h"
#include "Chert/LayerStack.h"

namespace chert {
    class Application
    {
    public:
        Application(WindowProps windowProps);
        void run();
        void onEvent(Event& e);
        bool onWindowClose(const WindowCloseEvent& e);

        void pushLayer(std::shared_ptr<Layer> layer);
        void pushOverlay(std::shared_ptr<Layer> overlay);

    private:
        std::unique_ptr<Window> window;
        bool running = true;
        LayerStack layerStack;
    };

    Application* CreateApplication();
}
