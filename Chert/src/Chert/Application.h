#pragma once

#include <memory>

#include "Chert/Core.h"
#include "Chert/Events/Event.h"
#include "Chert/Imgui/ImguiLayer.h"
#include "Chert/LayerStack.h"
#include "Chert/Renderer/Renderer.h"
#include "Chert/Window.h"

namespace chert {
class Application {
public:
    Application(WindowProps windowProps);
    virtual ~Application() = default;

    void prepare();
    void shutdown();
    void run();
    void onEvent(Event &e);
    bool onWindowClose(const WindowCloseEvent &e);
    void pushLayer(std::shared_ptr<Layer> layer);
    void pushOverlay(std::shared_ptr<Layer> overlay);
    void detachLayer(std::shared_ptr<Layer> layer);
    void detachOverlay(std::shared_ptr<Layer> overlay);
    inline Window &getWindow() { return *window; }

    virtual void init(){};

    static inline Application &get() { return *instance; }
    static inline Renderer &getRenderer() { return *instance->renderer; }
    static inline RenderingContext &getRenderContext() {
        return instance->renderer->getRenderContext();
    }
    static void initApplication();

private:
    std::unique_ptr<Window> window;
    std::unique_ptr<Renderer> renderer;

    LayerStack layerStack;
    std::shared_ptr<ImguiLayer> imguiLayer;

    bool running = true;

    float previousTime = 0.0f;

    static std::unique_ptr<Application> instance;
};

std::unique_ptr<Application> createApplication();
} // namespace chert
