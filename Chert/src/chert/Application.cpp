#include "Chert/Application.h"
#include "Chert/Log.h"
#include "Chert/Events/ApplicationEvent.h"

#include "GLFW/glfw3.h"

namespace chert {
    Application::Application(WindowProps windowProps) {
        window = std::unique_ptr<Window>(Window::create(windowProps));
        window->setEventCallback(std::bind(&Application::onEvent, this, std::placeholders::_1));
    }

    void Application::onEvent(Event& e) {
        CHERT_CORE_TRACE(e);
        EventDispatcher dispatcher(e);
        dispatcher.dispatch<WindowCloseEvent>(std::bind(&Application::onWindowClose, this, std::placeholders::_1));
    }

    void Application::run() {
        while (running) {   
            glClearColor(0.0f, 0.8f, 0.5f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT); 
            window->update();
        }
    }

    bool Application::onWindowClose(const WindowCloseEvent& e) {
        running = false;
        return true;
    }

}