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
        instance->prepare();
        Input::init();
        instance->init();
    }

    Application::Application(WindowProps windowProps) {
        window = Window::create(windowProps);
        window->setEventCallback(CHERT_BIND_EVENT_FN(Application::onEvent));
        imguiLayer = std::make_shared<ImguiLayer>();
    }

    void Application::prepare() {
        pushOverlay(imguiLayer);
        renderer = std::make_unique<Renderer>(window->getRenderingContext());
    }

    void Application::shutdown() {
        renderer.reset();
        layerStack.~LayerStack();
        window.reset();
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
            for (auto layer : layerStack) {
                layer->update();
            }

            imguiLayer->begin();
            renderer->render();
            imguiLayer->render();
            imguiLayer->end();

            window->update();
        }
    }

    bool Application::onWindowClose(const WindowCloseEvent& e) {
        running = false;
        return true;
    }

    void Application::pushLayer(std::shared_ptr<Layer> layer) {
        layerStack.pushLayer(layer);
    }

    void Application::pushOverlay(std::shared_ptr<Layer> overlay) {
        layerStack.pushOverlay(overlay);
    }

    void Application::detachLayer(std::shared_ptr<Layer> layer) {
        layerStack.detachLayer(layer);
    }

    void Application::detachOverlay(std::shared_ptr<Layer> overlay) {
        layerStack.detachOverlay(overlay);
    }

}