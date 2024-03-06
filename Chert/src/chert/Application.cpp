#include "Chert/Application.h"
#include "Chert/Log.h"
#include "Chert/Events/ApplicationEvent.h"

#include "glad/glad.h"

namespace chert {
    std::unique_ptr<Application> Application::instance;

    void Application::initApplication() {
        chert::Log::init();
        CHERT_CORE_ASSERT(!instance, "Application is already initialized");
        CHERT_CORE_INFO("Lauching Chert...");
        instance = chert::createApplication();
        instance->init();
    }

    Application::Application(WindowProps windowProps) {
        window = Window::create(windowProps);
        window->setEventCallback(std::bind(&Application::onEvent, this, std::placeholders::_1));
    }

    void Application::onEvent(Event& e) {
        EventDispatcher dispatcher(e);
        dispatcher.dispatch<WindowCloseEvent>(std::bind(&Application::onWindowClose, this, std::placeholders::_1));

        for (auto layerIt = layerStack.end(); layerIt != layerStack.begin(); ) {
            (*--layerIt)->onEvent(e);
            bool handled = std::visit([](auto&& e) -> bool {
                return e.isHandled();
                }, e);
            if (handled) {
                break;
            }
        }
    }

    void Application::run() {
        while (running) {
            glClearColor(0.0f, 0.8f, 0.5f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);

            for (auto layer : layerStack) {
                layer->update();
            }

            window->update();
        }
    }

    bool Application::onWindowClose(const WindowCloseEvent& e) {
        running = false;
        return true;
    }

    void Application::pushLayer(std::shared_ptr<Layer> layer)
    {
        layerStack.pushLayer(layer);
        layer->onAttach();
    }

    void Application::pushOverlay(std::shared_ptr<Layer> overlay)
    {
        layerStack.pushOverlay(overlay);
        overlay->onAttach();
    }

    void Application::detachLayer(std::shared_ptr<Layer> layer)
    {
        layer->onDetach();
        layerStack.detachLayer(layer);
    }

    void Application::detachOverlay(std::shared_ptr<Layer> overlay)
    {
        overlay->onDetach();
        layerStack.detachOverlay(overlay);
    }

}