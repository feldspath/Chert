#pragma once

#include <memory>

#include "Chert/Core.h"
#include "Chert/Window.h"
#include "Chert/Events/Event.h"
#include "Chert/LayerStack.h"
#include "Chert/Imgui/ImguiLayer.h"
#include "Chert/Renderer/Shader.h"

namespace chert {
    class Application
    {
    public:
        Application(WindowProps windowProps);
        virtual void init();
        void run();
        void onEvent(Event& e);
        bool onWindowClose(const WindowCloseEvent& e);

        void pushLayer(std::shared_ptr<Layer> layer);
        void pushOverlay(std::shared_ptr<Layer> overlay);
        void detachLayer(std::shared_ptr<Layer> layer);
        void detachOverlay(std::shared_ptr<Layer> overlay);

        inline Window& getWindow() { return *window; }

        static inline Application& get() { return *instance; }
        static void initApplication();

    private:
        std::unique_ptr<Window> window;
        bool running = true;
        LayerStack layerStack;

        static std::unique_ptr<Application> instance;

        unsigned int vertexBuffer = 0, indexBuffer = 0;
        std::unique_ptr<Shader> shader;

        ImguiLayer imguiLayer;
    };

    std::unique_ptr<Application> createApplication();
}
