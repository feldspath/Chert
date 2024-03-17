#pragma once

#include <memory>

#include "Chert/Core/Core.h"
#include "Chert/Core/LayerStack.h"
#include "Chert/Core/Window.h"
#include "Chert/Events/Event.h"
#include "Chert/Imgui/ImguiLayer.h"
#include "Chert/Renderer/Renderer.h"

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
    inline std::shared_ptr<Window> &getWindow() { return window; }

    virtual void init(){};

    static inline Application &get() { return *instance; }
    static inline std::shared_ptr<Renderer> &getRenderer() { return instance->renderer; }
    static inline std::shared_ptr<RenderingContext> &getRenderContext() {
        return instance->renderer->getRenderContext();
    }
    static void initApplication();

private:
    LayerStack layerStack;
    std::shared_ptr<Window> window;
    std::shared_ptr<Renderer> renderer;
    std::shared_ptr<ImguiLayer> imguiLayer;
    bool running = true;
    float previousTime = 0.0f;

    static std::unique_ptr<Application> instance;
};

std::unique_ptr<Application> createApplication();
} // namespace chert
