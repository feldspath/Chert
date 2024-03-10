#include "Chert/Application.h"
#include "Chert/Log.h"
#include "Chert/Events/ApplicationEvent.h"
#include "Chert/Input.h"

namespace chert {
    std::unique_ptr<Application> Application::instance;

    void Application::initApplication() {
        Log::init();
        CHERT_CORE_ASSERT(!instance, "Application is already initialized");
        CHERT_CORE_INFO("Lauching Chert...");
        instance = chert::createApplication();
        instance->Application::init();
        Input::init();
        instance->init();
    }

    Application::Application(WindowProps windowProps) {
        window = Window::create(windowProps);
        window->setEventCallback(CHERT_BIND_EVENT_FN(Application::onEvent));
    }

    void Application::init() {
        imguiLayer.init();
        
        renderer = std::make_unique<Renderer>(window->getRenderingContext());
    }

    void Application::onEvent(Event& e) {
        EventDispatcher dispatcher(e);
        dispatcher.dispatch<WindowCloseEvent>(CHERT_BIND_EVENT_FN(Application::onWindowClose));

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
            imguiLayer.begin();
            renderer->render();
            for (auto layer : layerStack) {
                layer->update();
            }
            imguiLayer.update();
            imguiLayer.end();

            window->update();
        }
    }

    bool Application::onWindowClose(const WindowCloseEvent& e) {
        running = false;
        return true;
    }

    void Application::pushLayer(std::shared_ptr<Layer> layer) {
        layerStack.pushLayer(layer);
        layer->onAttach();
    }

    void Application::pushOverlay(std::shared_ptr<Layer> overlay) {
        layerStack.pushOverlay(overlay);
        overlay->onAttach();
    }

    void Application::detachLayer(std::shared_ptr<Layer> layer) {
        layer->onDetach();
        layerStack.detachLayer(layer);
    }

    void Application::detachOverlay(std::shared_ptr<Layer> overlay) {
        overlay->onDetach();
        layerStack.detachOverlay(overlay);
    }

}